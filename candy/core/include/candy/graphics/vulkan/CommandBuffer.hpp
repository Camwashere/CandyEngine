#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
#include "../VertexArray.hpp"
#include "candy/graphics/shader/Shader.hpp"
namespace Candy::Graphics
{
    class CommandBuffer
    {
    private:
        VkCommandPool commandPool;
        //std::vector<VkCommandBuffer> commandBuffers;
        VkCommandBuffer mainCommandBuffer;
        
        
    private:
        void CreateCommandBuffers();
        void CreateCommandPool(VkSurfaceKHR surface);
        void Init(VkSurfaceKHR surface);
    public:
        explicit CommandBuffer(uint32_t currentFrame=0);
        ~CommandBuffer();
        
    public:
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
      void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        
    public:
        
        void Reset();
        void StartRecording(VkCommandBufferUsageFlags flags=0);
        void StartRenderPass(const VkRenderPassBeginInfo* renderPassInfo);
        void BindPipeline(VkPipeline pipeline);
        void SetViewport(VkExtent2D extent);
        void BindVertexBuffers(const std::vector<VkBuffer>& vertexBuffers);
        void BindIndexBuffer(const IndexBuffer& indexBuffer);
        void BindDescriptorSets(VkPipelineLayout layout, VkDescriptorSet descriptorSet);
        void Bind(const SharedPtr<VertexArray>& vertexArray);
        void DrawIndexed(const SharedPtr<VertexArray>& vertexArray);
        void EndRenderPass();
        void EndRecording();
        void EndAll();
        void Destroy();
        void PushConstants(VkPipelineLayout layout, ShaderStage shaderStage, uint32_t dataSize, const void* data);
        
    private:
        friend class GraphicsContext;
        friend class Renderer;
    };
}