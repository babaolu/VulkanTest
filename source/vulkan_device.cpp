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
		int score = rateDeviceSuitability(device);
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
