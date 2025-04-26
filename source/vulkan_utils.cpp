#include "HelloTriangle.hpp"

bool isDeviceSuitable(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	return deviceProperties.deviceType ==
		VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader;
}

int rateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	std::cout << "=> " << deviceProperties.deviceName << std::endl;

	int score = 0;
	QueueFamilyIndices indices = findQueueFamilies(device, surface);
	bool swapChainAdequate = false;
	bool extensionsSupported = checkDeviceExtensionSupport(device);

	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport =
			querySwapChainSupport(device, surface);
		swapChainAdequate = !(swapChainSupport.formats.empty() ||
				      swapChainSupport.presentModes.empty());
	}

	// Application can't function without geometry shaders
	if (!(deviceFeatures.geometryShader && indices.isComplete() &&
	      swapChainAdequate))
	{
		return 0;
	}

	// Discrete GPUs have a significant performance advantage
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 1000;
	}

	// Maximum possible size of textures affects graphics quality
	score += deviceProperties.limits.maxImageDimension2D;

	return score;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
				     VkSurfaceKHR surface)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
						 nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
						 queueFamilies.data());
	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (indices.isComplete())
			break;

		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
						     &presentSupport);
		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		i++;
	}

	return indices;
}

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device,
					      VkSurfaceKHR surface)
{
	SwapChainSupportDetails details;
	uint32_t formatCount, presentModeCount;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
						  &details.capabilities);

	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
					     nullptr);
	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface,
						     &formatCount,
						     details.formats.data());
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
						  &presentModeCount, nullptr);
	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
							   &presentModeCount,
							   details.presentModes.data());
	}

	return details;
}

std::vector<char> readFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	size_t fileSize = (size_t) file.tellg();
	std::cout << "File size: " << fileSize << std::endl;
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter,
			VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if (typeFilter & (1 << i) &&
		    (memProperties.memoryTypes[i].propertyFlags & properties) ==
			properties)
		{
			return i;
		}
	}

	throw std::runtime_error("Failed to find suitable memory type!");
}
