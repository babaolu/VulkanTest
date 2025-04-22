#include "HelloTriangle.hpp"

void HelloTriangleApp::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void HelloTriangleApp::framebufferResizeCallback(GLFWwindow *window,
							int width, int height)
{
	auto app = reinterpret_cast<HelloTriangleApp *>
		(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}
