#ifndef HELLO_TRIANGLE_HPP
#define HELLO_TRIANGLE_HPP

#define WIDTH 800
#define HEIGHT 600

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApp
{
	GLFWwindow *window;

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

#endif //HELLO_TRIANGLE_HPP
