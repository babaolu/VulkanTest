#include "HelloTriangle.hpp"

void HelloTriangleApp::initVulkan()
{
	createInstance();
	setupDebugMessenger();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createImageViews();
	createRenderPass();
	createDescriptorSetLayout();
	createGraphicsPipeline();
	createFramebuffers();
	createCommandPool();
	createVertexBuffer();
	createIndexBuffer();
	createUniformBuffers();
	createDescriptorPool();
	createDescriptorSets();
	createCommandBuffers();
	createSyncObjects();
}

void HelloTriangleApp::createInstance()
{
	uint32_t glfwExtensionCount = 0, extensionCount = 0;
	std::vector<const char*> glfwExtensions;

	if (enableValidationLayers && !checkValidationLayerSupport())
	{
		throw std::runtime_error(
			"Validation layers requested, but not available");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;


	glfwExtensions = getRequiredExtensions();
	glfwExtensionCount = glfwExtensions.size();

	// Checking for extension support
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
					       nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
					       extensions.data());

	VkExtensionProperties *pextensions = extensions.data();

	/* Array of pointers must always end with a nullptr for successfull
	 * checking
	 */
	char *extensionNamesArray[extensionCount + 1];
	char *glfwExtensionNames[glfwExtensionCount + 1];
	extensionNamesArray[extensionCount] = nullptr;
	glfwExtensionNames[glfwExtensionCount] = nullptr;

	std::cout << "Available extensions:\n";
	for (uint32_t iter = 0; iter < extensionCount; iter++)
	{
		extensionNamesArray[iter] = pextensions[iter].extensionName;
		std::cout << '\t' << extensionNamesArray[iter] << '\n';
	}
	std::cout << "Required extensions:\n";
	for (uint32_t iter = 0; iter < glfwExtensionCount; iter++)
	{
		glfwExtensionNames[iter] =
			const_cast<char *>(glfwExtensions[iter]);
		std::cout << '\t' << glfwExtensionNames[iter] << '\n';
	}

	if (pstrpstr(extensionNamesArray, glfwExtensionNames))
	{
		std::cout << "All required extensions available\n";
	} else
	{
		std::cout << "Required extensions not complete\n";
	}
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount =
			static_cast<uint32_t>(validationLayers.size() - 1);
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext =
			(VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
	} else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance");
	}
	std::cout << "Instance creation successful\n"
		  << "Instance: "<< instance << std::endl;
}

bool pstrpstr(char **haystack, char **needle)
{
	bool test;
	for (char **ppniter = needle; *ppniter != nullptr; ppniter++)
	{
		for (char **pphiter = haystack; *pphiter != nullptr;
		     pphiter++)
		{
			if (!strcmp(*pphiter, *ppniter))
			{
				test = true;
				break;
			}
			test = false;
		}
		if (!test) return (false);
	}
	return (true);
}

void HelloTriangleApp::createSurface()
{
	VkResult result = glfwCreateWindowSurface(instance, window, nullptr,
						  &surface);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create window surface!");
	}
}
