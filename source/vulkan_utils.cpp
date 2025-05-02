#include "HelloTriangle.hpp"

bool isDeviceSuitable(VkPhysicalDevice physicalDevice)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	return deviceProperties.deviceType ==
		VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader;
}

int rateDeviceSuitability(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
	vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

	std::cout << "=> " << deviceProperties.deviceName << std::endl;

	int score = 0;
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
	bool swapChainAdequate = false;
	bool extensionsSupported = checkDeviceExtensionSupport(physicalDevice);

	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport =
			querySwapChainSupport(physicalDevice, surface);
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

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice,
				     VkSurfaceKHR surface)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
						 nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
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
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface,
						     &presentSupport);
		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		i++;
	}

	return indices;
}

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice,
					      VkSurfaceKHR surface)
{
	SwapChainSupportDetails details;
	uint32_t formatCount, presentModeCount;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface,
						  &details.capabilities);

	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
					     nullptr);
	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface,
						     &formatCount,
						     details.formats.data());
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
						  &presentModeCount, nullptr);
	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface,
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
