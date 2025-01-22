#include "HelloTriangle.hpp"

VkSurfaceFormatKHR chooseSwapSurfaceFormat(
	const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
		    availableFormat.colorSpace ==
		    VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			if (enableValidationLayers)
			{
				std::cout <<
					"Preferred surface format selected\n";
			}
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(
	const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D HelloTriangleApp::chooseSwapExtent(
	const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width !=
	    std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	VkExtent2D actualExtent = {
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};
	actualExtent.width = std::clamp(actualExtent.width,
					capabilities.minImageExtent.width,
					capabilities.maxImageExtent.width);
	actualExtent.height = std::clamp(actualExtent.height,
					capabilities.minImageExtent.height,
					capabilities.maxImageExtent.height);

	return actualExtent;
}

void HelloTriangleApp::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport =
		querySwapChainSupport(physicalDevice, surface);

	VkSurfaceFormatKHR surfaceFormat =
		chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode =
		chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount <
	    swapChainSupport.capabilities.maxImageCount)
	{
		imageCount++;
	}

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
	uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(),
					 indices.presentFamily.value()};

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	if (queueFamilyIndices[0] != queueFamilyIndices[1])
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;  // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	createInfo.preTransform =
		swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr,
					       &swapChain);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapChain, &imageCount,
				swapChainImages.data());

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}
