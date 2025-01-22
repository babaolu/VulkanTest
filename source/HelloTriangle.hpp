#ifndef HELLO_TRIANGLE_HPP
#define HELLO_TRIANGLE_HPP

#define WIDTH 800
#define HEIGHT 600

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <limits>


const std::vector<const char *> validationLayers = {
	"VK_LAYER_KHRONOS_validation", nullptr
};

const std::vector<const char *> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME, nullptr
};

class HelloTriangleApp
{
	GLFWwindow *window;
	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	void createInstance();
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	VkExtent2D chooseSwapExtent(
		const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
};

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

std::vector<const char *> getRequiredExtensions();

bool checkValidationLayerSupport();

VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT *pcreateInfo,
	const VkAllocationCallbacks *pAllocator,
	VkDebugUtilsMessengerEXT *pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(
	VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator);

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
	void *pUserData);

void populateDebugMessengerCreateInfo(
	VkDebugUtilsMessengerCreateInfoEXT& createInfo);

bool isDeviceSuitable(VkPhysicalDevice);

bool checkDeviceExtensionSupport(VkPhysicalDevice);

int rateDeviceSuitability(VkPhysicalDevice, VkSurfaceKHR);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice, VkSurfaceKHR);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice, VkSurfaceKHR);

bool pstrpstr(char **, char **);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(
	const std::vector<VkSurfaceFormatKHR>&);

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);



#endif //HELLO_TRIANGLE_HPP
