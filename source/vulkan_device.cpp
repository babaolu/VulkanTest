#include "HelloTriangle.hpp"

void HelloTriangleApp::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		throw std::runtime_error(
			"Failed to fine GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	// Using an ordered map to automatically sort in increasing order
	std::multimap<int, VkPhysicalDevice> candidates;
	for (const auto& device : devices)
	{
		int score = rateDeviceSuitability(device, surface);
		candidates.insert(std::make_pair(score, device));
	}

	if (candidates.rbegin()->first > 0)
	{
		physicalDevice = candidates.rbegin()->second;
		std::cout << "Physical device selected" << std::endl;
	} else
	{
		throw std::runtime_error("Failed to find a suitable GPU!");
	}
}

void HelloTriangleApp::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
	float queuePriority = 1.0f;
	VkPhysicalDeviceFeatures deviceFeatures{};

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = {
		indices.graphicsFamily.value(), indices.presentFamily.value()
	};

	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType =
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount =
		static_cast<uint32_t>(queueCreateInfos.size());

	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount =
			static_cast<uint32_t>(validationLayers.size() - 1);
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else
	{
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr,
					 &device);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create logical device!");
	}
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0,
			 &graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily.value(), 0,
			 &presentQueue);
}
