cmake_minimum_required(VERSION 3.20)

project(VulkanTest)

add_executable(VulkanTest main.cpp
	main_loop.cpp
	window_init.cpp
	vulkan_init.cpp
	vulkan_device.cpp
	extensions.cpp
	vulkan_debug.cpp
	vulkan_utils.cpp
	clean_up.cpp)

target_link_libraries(VulkanTest -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi)
