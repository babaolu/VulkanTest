#include "HelloTriangle.hpp"

void HelloTriangleApp::cleanup()
{
	glfwDestroyWindow(window);

	glfwTerminate();
}
