#include "HelloTriangle.hpp"

void HelloTriangleApp::createCommandPool()
{
	QueueFamilyIndices queueFamilyIndices =
		findQueueFamilies(physicalDevice, surface);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr,
					      &commandPool);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create command pool!");
	}
}

void HelloTriangleApp::createCommandBuffer()
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	VkResult result = vkAllocateCommandBuffers(device, &allocInfo,
						   &commandBuffer);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate command buffers!");
	}
}

void HelloTriangleApp::recordCommandBuffer(VkCommandBuffer commandBuffer,
					   uint32_t imageIndex)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0;  // Optional
	beginInfo.pInheritanceInfo = nullptr;  // Optional

	VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to begin recording"
					 " command buffer!");
	}

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer= swapChainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = {0, 0};
	renderPassInfo.renderArea.extent = swapChainExtent;

	VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo,
			     VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			  graphicsPipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);

	vkCmdEndRenderPass(commandBuffer);

	result = vkEndCommandBuffer(commandBuffer);
	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to record command buffer!");
	}
}
