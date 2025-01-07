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
#include <cstring>
#include <stdexcept>
#include <cstdlib>

const std::vector<const char *> validationLayers = {
	"VK_LAYER_KHRONOS_validation", nullptr
};

class HelloTriangleApp
{
	GLFWwindow *window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	void createInstance();
	void setupDebugMessenger();
	void pickPhysicalDevice();

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

int rateDeviceSuitability(VkPhysicalDevice);

bool pstrpstr(char **, char **);

#endif //HELLO_TRIANGLE_HPP
