#include "HelloTriangle.hpp"

void HelloTriangleApp::cleanup()
{
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);

	glfwTerminate();
}
