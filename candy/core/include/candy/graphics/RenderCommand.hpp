#pragma once
#include <vulkan/vulkan.h>
#include <functional>
#include <CandyPch.hpp>
#include <candy/graphics/shader/ShaderData.hpp>
#include <candy/math/Vector.hpp>

namespace Candy::Graphics
{
  enum class RenderMode
  {
    Shaded=0,
    Wireframe=1,
    Point=2,
  };
  
  class CommandBuffer;
  struct FrameData;
  class VertexArray;
  class Pipeline;
  class RenderCommand
  {
  
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
    static void DrawEmpty(uint32_t count);
    static void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
    static void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, int32_t instanceCount=1, int32_t instanceIndex=0);
    static void DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count);
    static void BindPipeline(const Pipeline& pipeline);
    static void BindVertexArray(const VertexArray* vertexArray);
    static void SetClearColor(Color color);
    static void SetClearColor(float r, float g, float b);
    static void SetLineWidth(float value);
    
    static void SetRenderMode(RenderMode mode);
    static RenderMode GetRenderMode();
    
    static void BindDescriptorSets(const Pipeline& pipeline, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets);
    static void SetViewport(VkExtent2D extent);
    static void SetViewport(const Math::Vector2u& size);
    static void SetViewport(uint32_t width, uint32_t height);
    static void SetViewport(const Math::Vector2u& position, const Math::Vector2u& size);
    static void SetViewport(VkViewport viewport);
    static void PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t dataSize, const void* data);
    static void PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* data);
    static void SetUniform(uint32_t offset, uint32_t size, const void* data);
    static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    static void CopyBufferImmediate(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    static void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    static void CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height);
    static void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    
    static void Reset();
    static void ResetUtility();
    static void Submit();
    
    
  };
}