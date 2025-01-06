#include "HelloTriangle.hpp"

bool checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	VkLayerProperties availableLayers[layerCount];
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);
	char *layerNames[layerCount + 1];
	layerNames[layerCount] = nullptr;
	std::cout << "Available layer properties:\n";
	for (uint32_t iter = 0; iter < layerCount; iter++)
	{
		layerNames[iter] = availableLayers[iter].layerName;
		std::cout << '\t' << layerNames[iter] << '\n';
	}
	if (pstrpstr(layerNames, const_cast<char **>(validationLayers.data())))
	{
		std::cout << "Validation Layer supported" << std::endl;
		return (true);
	} else
	{
		std::cout << "Validation layer not supported" << std::endl;
		return (false);
	}
}

std::vector<const char *> getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions,
					    glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	return (extensions);
}
