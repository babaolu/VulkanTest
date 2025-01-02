#include "HelloTriangle.hpp"

void HelloTriangleApp::mainLoop()
{
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}
