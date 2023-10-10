#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Renderer2D.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/texture/TextureManager.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/graphics/vulkan/CommandPool.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/FrameResources.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/shader/config/ShaderProfile.hpp>
namespace Candy::Graphics
{
  
  
  struct RenderCommandData
  {
    VulkanBuffer* dummyBuffer=nullptr;
    GraphicsContext* target=nullptr;
    CommandPool uploadContext;
    //std::vector<CommandPool> renderCommandPools;
    RenderMode renderMode=RenderMode::Shaded;
    
  };
  static RenderCommandData data;
  
  void RenderCommand::SetRenderMode(RenderMode mode)
  {
    data.renderMode = mode;
  }
  
  RenderMode RenderCommand::GetRenderMode()
  {
    return data.renderMode;
  }
  

  
  VkCommandBufferBeginInfo RenderCommand::CommandBufferBeginInfo(VkCommandBufferUsageFlags flags)
  {
    CANDY_PROFILE_FUNCTION();
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;
    
    info.pInheritanceInfo = nullptr;
    info.flags = flags;
    return info;
  }
  VkSubmitInfo RenderCommand::SubmitInfo(VkCommandBuffer* cmd)
  {
    CANDY_PROFILE_FUNCTION();
    VkSubmitInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;
    
    info.waitSemaphoreCount = 0;
    info.pWaitSemaphores = nullptr;
    info.pWaitDstStageMask = nullptr;
    info.commandBufferCount = 1;
    info.pCommandBuffers = cmd;
    info.signalSemaphoreCount = 0;
    info.pSignalSemaphores = nullptr;
    
    return info;
  }
  
  
  void RenderCommand::Init(VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    data.uploadContext.Init(surface, CommandPoolType::OneTime, 1);
    data.dummyBuffer = new VulkanBuffer(BufferType::DUMMY);
  }
  

  /*VkDescriptorSet RenderCommand::GetGlobalDescriptorSet()
  {
    CANDY_PROFILE_FUNCTION();
    return Vulkan::GetCurrentContext().GetCurrentFrame().GlobalDescriptor();
  }*/
  VkCommandBuffer RenderCommand::GetRenderCommandBuffer()
  {
    return GetRenderCommandPool().GetCommandBuffer(0);
    //return GetRenderCommandPool().buffers[Renderer::GetCurrentPassIndex()];
  }
  CommandPool& RenderCommand::GetRenderCommandPool()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(data.target, "RenderCommand::GetRenderCommandPool() called before RenderCommand::SetTarget()!");
    return data.target->GetCurrentFrame().commandPool;
    //return data.renderCommandPools[Vulkan::GetCurrentContext().GetCurrentFrameIndex()];
  }
  FrameResources& RenderCommand::GetFrame()
  {
    CANDY_PROFILE_FUNCTION();
    return Vulkan::GetCurrentContext().GetCurrentFrame();
  }
  void RenderCommand::ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function)
  {
    CANDY_PROFILE_FUNCTION();
    VkCommandBuffer cmd = data.uploadContext.BeginCommandBuffer();
    
    //execute the function
    function(cmd);
    
    CANDY_VULKAN_CHECK(vkEndCommandBuffer(cmd));
    
    VkSubmitInfo submit = SubmitInfo(&cmd);
    
    
    //submit command buffer to the queue and execute it.
    // uploadFence will now block until the graphic commands finish execution
    CANDY_VULKAN_CHECK(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submit, data.uploadContext.fence));
    
    vkWaitForFences(Vulkan::LogicalDevice(), 1, &data.uploadContext.fence, true, 9999999999);
    vkResetFences(Vulkan::LogicalDevice(), 1, &data.uploadContext.fence);
    
    // reset the command buffers inside the command pool
    CANDY_VULKAN_CHECK(data.uploadContext.ResetBuffers());
  }
  void RenderCommand::DrawEmpty(uint32_t count)
  {
    CANDY_PROFILE_FUNCTION();
    // Bind the dummy buffer
    size_t offset = 0;
    VkBuffer vkBuffer = *data.dummyBuffer;
    vkCmdBindVertexBuffers(GetRenderCommandBuffer(), 0, 1, &vkBuffer, &offset);
    vkCmdDraw(GetRenderCommandBuffer(), count, 1, 0, 0);
  }
  
  void RenderCommand::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdDrawIndexed(GetRenderCommandBuffer(), indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
  }
  void RenderCommand::DrawIndexed(const SharedPtr<VertexArray>& vertexArray, int32_t instanceCount, int32_t instanceIndex)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdDrawIndexed(GetRenderCommandBuffer(), static_cast<uint32_t>(vertexArray->indexBuffer->GetCount()), instanceCount, 0, 0, instanceIndex);
  }
  
  void RenderCommand::DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32_t count)
  {
    CANDY_PROFILE_FUNCTION();
    vertexArray->Bind();
    vkCmdDraw(GetRenderCommandBuffer(), count, 1, 0, 0);
  }
  /*void RenderCommand::BindPipeline(const Pipeline& pipeline)
  {
    CANDY_PROFILE_FUNCTION();
    switch(pipeline.GetType())
    {
      case PipelineType::Graphics:
        vkCmdBindPipeline(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
        
        break;
      case PipelineType::Compute:
        vkCmdBindPipeline(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
        break;
      case PipelineType::RayTracing:
        vkCmdBindPipeline(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR, pipeline);
        break;
      default:
        CANDY_CORE_ASSERT(false, "Unknown pipeline type");
    }
  
  }*/
  
  void RenderCommand::BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdBindPipeline(GetRenderCommandBuffer(), bindPoint, pipeline);
  }
  
  
  void RenderCommand::BindVertexArray(const VertexArray* vertexArray)
  {
    CANDY_PROFILE_FUNCTION();
    
    VkBuffer vertexBuffers[vertexArray->vertexBuffers.size()];
    for (int i = 0; i<vertexArray->vertexBuffers.size(); i++)
    {
      vertexBuffers[i] = *vertexArray->vertexBuffers[i];
    }
    vkCmdBindVertexBuffers(GetRenderCommandBuffer(), 0, vertexArray->vertexBuffers.size(), vertexBuffers, vertexArray->vertexBufferOffsets.data());
    if (vertexArray->indexBuffer)
    {
      vkCmdBindIndexBuffer(GetRenderCommandBuffer(), *vertexArray->indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    }
  }
  void RenderCommand::SetClearColor(Color color)
  {
    CANDY_PROFILE_FUNCTION();
    Renderer::SetClearColor(color);
  }
  void RenderCommand::SetClearColor(float r, float g, float b)
  {
    CANDY_PROFILE_FUNCTION();
    SetClearColor({r, g, b});
  }
  void RenderCommand::SetLineWidth(float value)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdSetLineWidth(GetRenderCommandBuffer(), value);
  }
  
  /*void RenderCommand::BindDescriptorSets(const Pipeline& pipeline, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets)
  {
    CANDY_PROFILE_FUNCTION();
    
    if (uniformOffsets.empty())
    {
      vkCmdBindDescriptorSets(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetLayout(), firstSet, descriptorSets.size(), descriptorSets.data(), 0, nullptr);
    }
    else
    {
      vkCmdBindDescriptorSets(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetLayout(), firstSet, descriptorSets.size(), descriptorSets.data(), uniformOffsets.size(), uniformOffsets.data());
    }
  }*/
  
  void RenderCommand::BindDescriptorSets(VkPipelineLayout pipelineLayout, uint32_t firstSet, const std::vector<VkDescriptorSet>& descriptorSets, const std::vector<uint32_t>& uniformOffsets)
  {
    CANDY_PROFILE_FUNCTION();
    if (uniformOffsets.empty())
    {
      vkCmdBindDescriptorSets(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, firstSet, descriptorSets.size(), descriptorSets.data(), 0, nullptr);
    }
    else
    {
      vkCmdBindDescriptorSets(GetRenderCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, firstSet, descriptorSets.size(), descriptorSets.data(), uniformOffsets.size(), uniformOffsets.data());
    }
  }
  
  void RenderCommand::SetViewport(VkExtent2D extent)
  {
    CANDY_PROFILE_FUNCTION();
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(extent.width);
    viewport.height = static_cast<float>(extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    
    
    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = extent;
    
    vkCmdSetViewport(GetRenderCommandBuffer(), 0, 1, &viewport);
    vkCmdSetScissor(GetRenderCommandBuffer(), 0, 1, &scissor);
  }
  void RenderCommand::SetViewport(const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    SetViewport(VkExtent2D{size.x, size.y});
  }
  void RenderCommand::SetViewport(uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    SetViewport(VkExtent2D{width, height});
  }
  void RenderCommand::SetViewport(const Math::Vector2u& position, const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    VkViewport viewport{};
    viewport.x = position.x;
    viewport.y = position.y;
    viewport.width = size.width;
    viewport.height = size.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    SetViewport(viewport);
    
  }
  void RenderCommand::SetViewport(VkViewport viewport)
  {
    CANDY_PROFILE_FUNCTION();
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{};
    scissor.offset.x = viewport.x;
    scissor.offset.y = viewport.y;
    scissor.extent = VkExtent2D(static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height));
    
    vkCmdSetViewport(GetRenderCommandBuffer(), 0, 1, &viewport);
    vkCmdSetScissor(GetRenderCommandBuffer(), 0, 1, &scissor);
  }
  
  void RenderCommand::SetDepthTestsEnabled(bool depthTestEnabled, bool biasEnabled, bool boundsTestEnabled)
  {
    vkCmdSetDepthTestEnable(GetRenderCommandBuffer(), depthTestEnabled);
    vkCmdSetDepthBiasEnable(GetRenderCommandBuffer(), depthTestEnabled && biasEnabled);
    vkCmdSetDepthBoundsTestEnable(GetRenderCommandBuffer(), depthTestEnabled && boundsTestEnabled);
  }
  void RenderCommand::SetDepthTestEnabled(bool enabled)
  {
    vkCmdSetDepthTestEnable(GetRenderCommandBuffer(), enabled);
  }
  void RenderCommand::SetDepthBias(float clamp, float constantFactor, float slopeFactor)
  {
    vkCmdSetDepthBias(GetRenderCommandBuffer(), clamp, constantFactor, slopeFactor);
  }
  void RenderCommand::SetDepthBounds(float min, float max)
  {
    vkCmdSetDepthBounds(GetRenderCommandBuffer(), min, max);
  }
  void RenderCommand::SetBlendConstants(const Math::Vector4& constants)
  {
    vkCmdSetBlendConstants(GetRenderCommandBuffer(), constants.data);
  }
  void RenderCommand::SetCullMode(VkCullModeFlags mode)
  {
    vkCmdSetCullMode(GetRenderCommandBuffer(), mode);
  }
  void RenderCommand::SetStencilCompareMask(VkStencilFaceFlags faceMask, uint32_t compareMask)
  {
    vkCmdSetStencilCompareMask(GetRenderCommandBuffer(), faceMask, compareMask);
  }
  
  void RenderCommand::SetUniform(uint32_t offset, uint32_t size, const void* uniformData)
  {
    CANDY_PROFILE_FUNCTION();
    GetFrame().uniformBuffer->SetData(offset, size, uniformData);
  }
  void RenderCommand::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    //GetCommandBuffer().CopyBuffer(srcBuffer, dstBuffer, size);
  }
  void RenderCommand::CopyBufferImmediate(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    CANDY_PROFILE_FUNCTION();
    ImmediateSubmit([=](VkCommandBuffer cmd)
                    {
                      VkBufferCopy copyRegion{};
                      copyRegion.srcOffset = 0; // Optional
                      copyRegion.dstOffset = 0; // Optional
                      copyRegion.size = size;
                      vkCmdCopyBuffer(cmd, srcBuffer, dstBuffer, 1, &copyRegion);
                    });
  }
 
  
  void RenderCommand::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
  {
    CANDY_PROFILE_FUNCTION();
    
    ImmediateSubmit([=](VkCommandBuffer cmd)
    {
      VkImageMemoryBarrier barrier{};
      barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
      barrier.oldLayout = oldLayout;
      barrier.newLayout = newLayout;
      
      barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
      barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
      
      barrier.image = image;
      
      barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      barrier.subresourceRange.baseMipLevel = 0;
      barrier.subresourceRange.levelCount = 1;
      barrier.subresourceRange.baseArrayLayer = 0;
      barrier.subresourceRange.layerCount = 1;
      
      VkPipelineStageFlags sourceStage;
      VkPipelineStageFlags destinationStage;
      if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL || GraphicsContext::IsDepthOnlyFormat(format))
      {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        
        if (GraphicsContext::HasStencilComponent(format))
        {
          barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
        }
      }
      else
      {
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      }
      if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
      {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
      }
      else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
      {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
      }
      else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
      {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
      }
      else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
      {
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; // OR VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, depending on usage
      }
      else if (oldLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
      {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        
        sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
      }
      else
      {
        CANDY_CORE_ASSERT(false, "Unsupported layout transition!");
      }
      vkCmdPipelineBarrier(cmd, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    });
    
    
  }
  
  
  void RenderCommand::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    ImmediateSubmit([=](VkCommandBuffer cmd)
    {
      VkBufferImageCopy region{};
      region.bufferOffset = 0;
      region.bufferRowLength = 0;
      region.bufferImageHeight = 0;
      
      region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      region.imageSubresource.mipLevel = 0;
      region.imageSubresource.baseArrayLayer = 0;
      region.imageSubresource.layerCount = 1;
      
      region.imageOffset = {0, 0, 0};
      region.imageExtent = {width, height, 1};
      
      vkCmdCopyBufferToImage(cmd, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    });
    
  }
  
  void RenderCommand::CopyImageToBuffer(VkImage image, VkBuffer buffer, uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    
    
    ImmediateSubmit([=](VkCommandBuffer cmd)
    {
      VkBufferImageCopy region{};
      region.bufferOffset = 0;
      region.bufferRowLength = 0; // Specifying 0 means tightly packed
      region.bufferImageHeight = 0; // Specifying 0 means tightly packed
      
      region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      region.imageSubresource.mipLevel = 0;
      region.imageSubresource.baseArrayLayer = 0;
      region.imageSubresource.layerCount = 1;
      
      region.imageOffset = {0, 0, 0};
      region.imageExtent = {width, height, 1};
      
      vkCmdCopyImageToBuffer(cmd, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);

// Copy from image to buffer
      
      VkBufferMemoryBarrier barrier{};
      barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
      barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT; // We have written to the buffer
      barrier.dstAccessMask = VK_ACCESS_HOST_READ_BIT; // Prepare for host read access
      barrier.buffer = buffer; // Buffer where the data was copied
      barrier.size = VK_WHOLE_SIZE; // Apply to entire buffer
      barrier.offset = 0;
      
      vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, // After the transfer stage
      VK_PIPELINE_STAGE_HOST_BIT, // Before the host operation
      0, 0, nullptr, 1, &barrier, // Buffer memory barrier
      0, nullptr);
    });
    
    
    
  }
  void RenderCommand::CopyImageToBuffer(VkImage image, VkBuffer buffer, int x, int y, uint32_t width, uint32_t height)
  {
    CANDY_PROFILE_FUNCTION();
    
    ImmediateSubmit([=](VkCommandBuffer cmd)
    {
      VkBufferImageCopy region{};
      region.bufferOffset = 0;
      region.bufferRowLength = 0; // Specifying 0 means tightly packed
      region.bufferImageHeight = 0; // Specifying 0 means tightly packed
      
      region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      region.imageSubresource.mipLevel = 0;
      region.imageSubresource.baseArrayLayer = 0;
      region.imageSubresource.layerCount = 1;
      
      region.imageOffset = {x, y, 0};
      region.imageExtent = {width, height, 1};
      
      
      vkCmdCopyImageToBuffer(cmd, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &region);


// Copy from image to buffer
      
      VkBufferMemoryBarrier barrier{};
      barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
      barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT; // We have written to the buffer
      barrier.dstAccessMask = VK_ACCESS_HOST_READ_BIT; // Prepare for host read access
      barrier.buffer = buffer; // Buffer where the data was copied
      barrier.size = VK_WHOLE_SIZE; // Apply to entire buffer
      barrier.offset = 0;
      
      vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, // After the transfer stage
      VK_PIPELINE_STAGE_HOST_BIT, // Before the host operation
      0, 0, nullptr, 1, &barrier, // Buffer memory barrier
      0, nullptr);
    });
    
    
    
  }
  
  
  
  
  
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t dataSize, const void* pushData)
  {
    CANDY_PROFILE_FUNCTION();
    PushConstants(pipelineLayout, stage, 0, dataSize, pushData);
  }
  void RenderCommand::PushConstants(VkPipelineLayout pipelineLayout, ShaderData::Stage stage, uint32_t offset, uint32_t dataSize, const void* pushData)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdPushConstants(GetRenderCommandBuffer(), pipelineLayout, ShaderData::StageToVulkan(stage), offset, dataSize, pushData);
  }
  
  void RenderCommand::BeginRenderPass(const VkRenderPassBeginInfo* renderPassBeginInfo)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdBeginRenderPass(GetRenderCommandBuffer(), renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    
  }
  
  void RenderCommand::NextRenderPass(const VkRenderPassBeginInfo* renderPassInfo)
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdEndRenderPass(GetRenderCommandBuffer());
    vkCmdBeginRenderPass(GetRenderCommandBuffer(), renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  }
  
  void RenderCommand::EndRenderPass()
  {
    CANDY_PROFILE_FUNCTION();
    vkCmdEndRenderPass(GetRenderCommandBuffer());
  }
  
  

  
  void RenderCommand::Submit()
  {
    CANDY_PROFILE_FUNCTION();
    const std::vector<VkCommandBuffer>& renderBuffers = GetRenderCommandPool().buffers;
    for (auto buffer : renderBuffers)
    {
      
      vkEndCommandBuffer(buffer);
    }
    
    
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount=renderBuffers.size();
    submitInfo.pCommandBuffers = renderBuffers.data();
    
    
    
    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    
    submitInfo.pWaitDstStageMask = &waitStage;
    
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &GetFrame().presentSemaphore;
    
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &GetFrame().renderSemaphore;
    
    CANDY_VULKAN_CHECK(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, GetRenderCommandPool().fence));
  }
  void RenderCommand::SetTarget(GraphicsContext* context)
  {
    data.target = context;
  }
  VkFence RenderCommand::GetCurrentRenderFence()
  {
    return GetRenderCommandPool().fence;
  }
}