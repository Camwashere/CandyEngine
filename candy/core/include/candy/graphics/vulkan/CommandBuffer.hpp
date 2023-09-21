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
        std::array<VkCommandBuffer, 4> commandBuffers;
        std::array<bool, 4> activeBuffers;
        //VkCommandBuffer utilityBuffer;
        uint8_t currentBuffer=0;
        //VkCommandBuffer mainCommandBuffer;
        
        
        
    private:
        void CreateCommandBuffers();
        void CreateCommandPool(VkSurfaceKHR surface);
        void Init(VkSurfaceKHR surface);
        
    public:
    
    public:
        explicit CommandBuffer(uint32_t currentFrame=0);
        ~CommandBuffer()=default;
        
        operator VkCommandBuffer(){return GetCurrentBuffer();}
        
        
    public:
      void SetCurrentBuffer(uint8_t index);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize srcOffset=0, VkDeviceSize dstOffset=0);
        void CopyBufferImmediate(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
      void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
     
      
        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height);
        void CopyImageToBuffer(VkImage image, VkBuffer buffer, int x, int y, uint32_t width, uint32_t height);
        
    public:
        
        void Reset();
        void ResetUtility();
        void StartRecording(VkCommandBufferUsageFlags flags=0);
        void StartRenderPass(const VkRenderPassBeginInfo* renderPassInfo);
        
    public:
      VkCommandBuffer& GetCurrentBuffer();
      VkCommandBuffer& GetViewportBuffer();
      VkCommandBuffer& GetOverlayBuffer();
      VkCommandBuffer& GetSelectionBuffer();
      VkCommandBuffer& GetUIBuffer();
      //VkCommandBuffer& GetUtilityBuffer();
      std::vector<VkCommandBuffer> GetActiveBuffers();
      const std::array<VkCommandBuffer, 4>& GetBuffers();
      size_t GetBufferCount()const;
      
        void BindGraphicsPipeline(VkPipeline pipeline);
        void BindComputePipeline(VkPipeline pipeline);
        void SetViewport(VkExtent2D extent);
        void SetViewport(VkViewport viewport);
        void SetLineWidth(float value);
        
        void BindVertexBuffers(const std::vector<VkBuffer>& vertexBuffers);
        void BindIndexBuffer(const IndexBuffer& indexBuffer);
        //void BindDescriptorSet(VkPipelineLayout layout, VkDescriptorSet descriptorSet, const uint32_t* uniformOffset);
        void BindDescriptorSets(VkPipelineLayout layout, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets);
        
        void BindVertexArray(const VertexArray* vertexArray);
        void DrawEmpty(uint32_t count, VkBuffer dummyBuffer);
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
        void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, int32_t instanceCount=1, int32_t instanceIndex=0);
        void DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count);
        void EndRenderPass(uint8_t index);
        void EndRenderPasses();
        void EndRecording(uint8_t index);
        void EndRecordings();
        void End(uint8_t index);
        void EndUtility();
        void EndAll();
        //void EndAll();
        //void Destroy();
        void PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t dataSize, const void* data);
        void PushConstants(VkPipelineLayout layout, ShaderData::Stage shaderStage, uint32_t offset, uint32_t dataSize, const void* data);
        
    private:
        friend class GraphicsContext;
        //friend class Renderer;
        friend class RenderCommand;
    };
}