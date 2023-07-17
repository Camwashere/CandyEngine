#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
#include "../VertexArray.hpp"
#include "../Shader.hpp"
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
        
    public:
        void Reset();
        void StartRecording(VkCommandBufferUsageFlags flags=0);
        //void StartRecording(uint32_t currentFrame);
        void StartRenderPass(const VkRenderPassBeginInfo* renderPassInfo);
        void BindPipeline(VkPipeline pipeline);
        void SetViewport(VkExtent2D extent);
        void BindVertexBuffers(const std::vector<VkBuffer>& vertexBuffers);
        void BindIndexBuffer(const IndexBuffer& indexBuffer);
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