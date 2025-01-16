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

	// Application can't function without geometry shaders
	if (!(deviceFeatures.geometryShader && indices.isComplete()))
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
