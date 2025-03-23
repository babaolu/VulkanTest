#include "HelloTriangle.hpp"

void HelloTriangleApp::mainLoop()
{
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		drawFrame();
	}
	vkDeviceWaitIdle(device);
}

void HelloTriangleApp::drawFrame()
{
	vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE,
			UINT64_MAX);
	vkResetFences(device, 1, &inFlightFences[currentFrame]);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(device, swapChain, UINT64_MAX,
			      imageAvailableSemaphores[currentFrame],
			      VK_NULL_HANDLE, &imageIndex);

	vkResetCommandBuffer(commandBuffers[currentFrame], 0);

	recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = {
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

	VkSemaphore signalSemaphores[] =
		{renderFinishedSemaphores[currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	VkResult result = vkQueueSubmit(graphicsQueue, 1, &submitInfo,
					inFlightFences[currentFrame]);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit draw command "
					 "buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;  // Optional

	result = vkQueuePresentKHR(presentQueue, &presentInfo);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to present!");
	}
	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
