#pragma once

#include "Vulkan.h"
#include "glm/glm.hpp"
#include "Texture.h"

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

	struct Camera
	{
		glm::vec3 Position{ 0, 0, 8 };
		glm::vec3 Rotation{ 0, 0, 0 };
	};

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
	};

	class Renderer
	{
	public:
		void Init();
		void Shutdown();

		void BeginScene(const Camera& camera);
		void EndScene(const Camera& camera);

		void RenderCube(const glm::vec3& position, const glm::vec3& rotation);
		void RenderUI();
	public:
		static uint32_t GetVulkanMemoryType(VkMemoryPropertyFlags properties, uint32_t type_bits)
		{
			VkPhysicalDevice physicalDevice = GetVulkanInfo()->PhysicalDevice;

			VkPhysicalDeviceMemoryProperties prop;
			vkGetPhysicalDeviceMemoryProperties(physicalDevice, &prop);
			for (uint32_t i = 0; i < prop.memoryTypeCount; i++)
				if ((prop.memoryTypes[i].propertyFlags & properties) == properties && type_bits & (1 << i))
					return i;
			return 0xFFFFFFFF; // Unable to find memoryType
		}
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

		std::shared_ptr<Texture> m_Texture;
	};
}