cmake_minimum_required(VERSION 3.20)

project(VulkanTest)

add_subdirectory(shaders)

add_executable(VulkanTest main.cpp
	main_loop.cpp
	window_init.cpp
	vulkan_init.cpp
	vulkan_device.cpp
	vulkan_swap.cpp
	vulkan_image.cpp
	vulkan_pipeline.cpp
	extensions.cpp
	vulkan_debug.cpp
	vulkan_utils.cpp
	clean_up.cpp)

target_link_libraries(VulkanTest -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi)

# Ensure shaders are compiled before building VulkanTest
add_dependencies(VulkanTest ShaderTargets)
