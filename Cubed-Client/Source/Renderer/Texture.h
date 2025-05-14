#pragma once

#include "Walnut/Core/Buffer.h"
#include "Vulkan.h"

namespace Cubed
{
	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height, Walnut::Buffer data);
		~Texture();
	private:
		void Init(Walnut::Buffer data);
	private:
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		VkImage m_Image = nullptr;
		VkDeviceMemory m_Memory = nullptr;
		VkImageView m_ImageView = nullptr;
		VkSampler m_Sampler = nullptr;
	};
}