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

	void createInstance();
	bool checkValidationLayerSupport();

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

bool pstrpstr(char **, char **);

#endif //HELLO_TRIANGLE_HPP
