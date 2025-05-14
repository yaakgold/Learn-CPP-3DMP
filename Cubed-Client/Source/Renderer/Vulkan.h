#pragma once

#include "Vulkan/Vulkan.h"

#include <iostream>
#include <string>
#include <backends/imgui_impl_vulkan.h>
#include <glm/glm.hpp>

namespace vkb
{
	const std::string to_string(VkResult result);
}

namespace Cubed
{
	ImGui_ImplVulkan_InitInfo* GetVulkanInfo();
}

#define VK_CHECK(x)                                                                    \
	do                                                                                 \
	{                                                                                  \
		VkResult err = x;                                                              \
		if (err)                                                                       \
		{                                                                              \
			std::cout << "Vulkan error: " + vkb::to_string(err);					   \
		}                                                                              \
	} while (0)