#ifndef HELLO_TRIANGLE_HPP
#define HELLO_TRIANGLE_HPP

#define WIDTH 800
#define HEIGHT 600

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApp
{
	GLFWwindow *window;
	VkInstance instance;

	void createInstance();

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
