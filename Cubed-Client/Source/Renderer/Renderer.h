#pragma once

#include "../Vulkan.h"

#include <filesystem>

namespace Cubed
{
	struct Buffer
	{
		VkBuffer Handle = nullptr;
		VkDeviceMemory Memory = nullptr;
		VkDeviceSize Size = 0;
		VkBufferUsageFlagBits Usage = VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
	};

	class Renderer
	{
	public:
		void Init();
		void Shutdown();

		void RenderCube(const glm::vec3& position, const glm::vec3& rotation);
		void RenderUI();
	private:
		void InitPipeline();
		void InitBuffers();
		void CreateOrResizeBuffer(Buffer& buffer, uint32_t newSize);

		VkShaderModule LoadShaders(const std::filesystem::path& path);
	private:
		VkPipeline m_GraphicsPipeline = nullptr;
		VkPipelineLayout m_PipelineLayout = nullptr;

		Buffer m_VertexBuffer, m_IndexBuffer;

		struct PushConstants
		{
			glm::mat4 ViewProjection;
			glm::mat4 Transform;
		} m_PushConstants;

		glm::vec3 m_CameraPosition{ 0, 0, 8 };
		glm::vec3 m_CameraRotation{ 0 };
	};
}