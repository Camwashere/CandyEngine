#pragma once
#include <vulkan/vulkan.h>
#include <functional>
#include <CandyPch.hpp>
#include "VertexArray.hpp"
#include <candy/math/Vector.hpp>
#include "vulkan/pipeline/Pipeline.hpp"
#include <candy/graphics/GraphicsContext.hpp>
namespace Candy::Graphics
{
  struct UploadContext
  {
    VkFence uploadFence;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
  };
  
  class RenderCommand
  {
    private:
    static UploadContext uploadContext;
  private:
    static VkCommandBufferBeginInfo CommandBufferBeginInfo(VkCommandBufferUsageFlags flags=0);
    static VkSubmitInfo SubmitInfo(VkCommandBuffer* cmd);
    static void InitCommands();
    static void InitSyncStructures();
    static CommandBuffer& GetCommandBuffer();
    static VkDescriptorSet GetGlobalDescriptorSet();
    
    static FrameData& GetFrame();
    
  public:
    static void Init();
    static void ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function);
    
  public:
    static void DrawIndexed(const SharedPtr<VertexArray>& vertexArray);
    static void BindPipeline(const Pipeline& pipeline);
    static void BindVertexArray(const VertexArray* vertexArray);
    //static void BindDescriptorSet(const Pipeline& pipeline, VkDescriptorSet descriptorSet, uint32_t uniformOffset);
    static void BindDescriptorSets(const Pipeline& pipeline, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets);
    static void SetViewport(VkExtent2D extent);
    static void SetViewport(const Math::Vector2u& size);
    static void SetViewport(uint32_t width, uint32_t height);
    static void SetViewport(const Math::Vector2u& position, const Math::Vector2u& size);
    static void SetViewport(VkViewport viewport);
    static void PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t dataSize, const void* data);
    static void PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data);
    static void SetUniform(uint32_t offset, uint32_t size, const void* data);
    
    static void Reset();
    static void Submit();
    
    
  };
}