#include <candy/graphics/GraphicsContext.hpp>
#include <CandyPch.hpp>
#include <GLFW/glfw3.h>
#include <set>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/FrameResources.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  
    GraphicsContext::GraphicsContext(GLFWwindow* window, VkSurfaceKHR windowSurface) : handle(window), surface(windowSurface)
    {
      CANDY_PROFILE_FUNCTION();
      InitSyncStructures();
      swapChain = CreateUniquePtr<SwapChain>(this, Renderer::GetUIPass());
      CreateViewport();
      
    }
  
  void GraphicsContext::InitSyncStructures()
  {
    CANDY_PROFILE_FUNCTION();
    
    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    
    
    frames.resize(Vulkan::GetFramesInFlight());
    
    for (int i = 0; i<Vulkan::GetFramesInFlight(); i++)
    {
      frames[i].descriptorSets.resize(4);
      frames[i].commandPool.Init(surface, CommandPoolType::LongLived, 1, !(bool)i);
      CANDY_VULKAN_CHECK(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].presentSemaphore));
      CANDY_VULKAN_CHECK(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].renderSemaphore));
      CANDY_VULKAN_CHECK(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].computeSemaphore));
      CANDY_VULKAN_CHECK(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].transferSemaphore));
      frames[i].uniformBuffer = UniformBuffer::Create();
      frames[i].storageBuffer = StorageBuffer::Create(sizeof(Matrix4), MAX_OBJECTS);
      frames[i].materialBuffer = UniformBuffer::Create();
      Vulkan::DeletionQueue().Push(frames[i].presentSemaphore);
      Vulkan::DeletionQueue().Push(frames[i].renderSemaphore);
      Vulkan::DeletionQueue().Push(frames[i].computeSemaphore);
      Vulkan::DeletionQueue().Push(frames[i].transferSemaphore);
    }
    
  }
  void GraphicsContext::RecreateViewport()
  {
    CANDY_PROFILE_FUNCTION();
      CleanViewport();
      CreateViewport();
      
      for (int i=0; i<Vulkan::GetFramesInFlight(); i++)
      {
        ImGui_ImplVulkan_RemoveTexture(frames[i].viewportData.viewportDescriptor);
        ImGui_ImplVulkan_RemoveTexture(frames[i].viewportData.viewportDepthDescriptor);
        
        frames[i].viewportData.viewportDescriptor = ImGui_ImplVulkan_AddTexture(frames[i].viewportData.viewportImageView.GetSampler(), frames[i].viewportData.viewportImageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        frames[i].viewportData.viewportDepthDescriptor = ImGui_ImplVulkan_AddTexture(frames[i].viewportData.depthImageView.GetSampler(), frames[i].viewportData.depthImageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      }
  }
  void GraphicsContext::CreateViewport()
  {
    CANDY_PROFILE_FUNCTION();
    Vector2u size = {swapChain->extent.width, swapChain->extent.height};
      for (int i=0; i<Vulkan::GetFramesInFlight(); i++)
      {
        CreateDepthResources(i, size);
        frames[i].viewportData.viewportImage.Create(size, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
        frames[i].viewportData.viewportImageView.Set(frames[i].viewportData.viewportImage);
        
        frames[i].viewportData.selectionImage.Create(size, VK_FORMAT_R32_SINT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
        frames[i].viewportData.selectionImageView.Set(frames[i].viewportData.selectionImage);
        
        frames[i].viewportData.viewportFrameBuffer.Set(Renderer::GetViewportPass(), size, {frames[i].viewportData.viewportImageView, frames[i].viewportData.depthImageView});
        frames[i].viewportData.selectionFrameBuffer.Set(Renderer::GetSelectionPass(), size, {frames[i].viewportData.selectionImageView, frames[i].viewportData.depthImageView});
        
        RenderCommand::TransitionImageLayout(frames[i].viewportData.viewportImage, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        RenderCommand::TransitionImageLayout(frames[i].viewportData.selectionImage, VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        
        frames[i].viewportData.selectionPixelBuffer = new PixelBuffer(size);
      }
  }
  
  void GraphicsContext::CleanViewport()
  {
    CANDY_PROFILE_FUNCTION();
    for (int i=0; i<Vulkan::GetFramesInFlight(); i++)
    {
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.depthImage);
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.depthImageView);
      
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.selectionFrameBuffer);
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.selectionImage);
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.selectionImageView);
      Vulkan::DeletionQueue().Delete(frames[i].viewportData.selectionPixelBuffer);
      delete frames[i].viewportData.selectionPixelBuffer;
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.viewportFrameBuffer);
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.viewportImage);
      Vulkan::DeletionQueue().Delete(&frames[i].viewportData.viewportImageView);
    }
   
  }
  
  

  
  bool GraphicsContext::HasStencilComponent(VkFormat format)
  {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
  }
  bool GraphicsContext::IsDepthOnlyFormat(VkFormat format)
  {
    switch(format)
    {
      case VK_FORMAT_D16_UNORM:
      case VK_FORMAT_D32_SFLOAT:
      case VK_FORMAT_X8_D24_UNORM_PACK32:
        return true;
      default:
        return false;
    }
  }
  VkFormat GraphicsContext::FindDepthFormat()
  {
    return FindSupportedFormat(
      {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
      VK_IMAGE_TILING_OPTIMAL,
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
  }
  VkFormat GraphicsContext::FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
  {
    CANDY_PROFILE_FUNCTION();
    for (VkFormat format : candidates)
    {
      VkFormatProperties props;
      vkGetPhysicalDeviceFormatProperties(Vulkan::PhysicalDevice(), format, &props);
      if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
      {
        return format;
      }
      else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
      {
        return format;
      }
    }
    
    CANDY_CORE_ASSERT(false, "Failed to find supported format!");
    return VK_FORMAT_UNDEFINED;
    
  }
  
    void GraphicsContext::NextSwapChainImage()
    {
      CANDY_PROFILE_FUNCTION();
      
      CANDY_VULKAN_CHECK(frames[currentFrameIndex].commandPool.WaitFence());
      CANDY_VULKAN_CHECK(frames[currentFrameIndex].commandPool.ResetPool());
      UpdateFrameIndex();
      VkResult result = swapChain->AcquireNextImage(GetCurrentFrame().presentSemaphore, UINT64_MAX);
      
      if (result == VK_ERROR_OUT_OF_DATE_KHR)
      {
        frameBufferResized = false;
        swapChain->Rebuild(Renderer::GetUIPass());
        RecreateViewport();
      }
      else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
      {
        CANDY_CORE_ASSERT(false, "Failed to acquire swap chain image!");
      }
     
    }
  void GraphicsContext::Submit()
  {
    CANDY_PROFILE_FUNCTION();
    GetCurrentFrame().commandPool.EndRecording();
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = GetCurrentFrame().commandPool.buffers.size();
    submitInfo.pCommandBuffers = GetCurrentFrame().commandPool.buffers.data();
    
    
    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    
    submitInfo.pWaitDstStageMask = &waitStage;
    
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &GetCurrentFrame().presentSemaphore;
    
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &GetCurrentFrame().renderSemaphore;
    
    
    CANDY_VULKAN_CHECK(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submitInfo, GetCurrentFrame().commandPool.fence));
  }
    void GraphicsContext::Present()
    {
      CANDY_PROFILE_FUNCTION();
      VkPresentInfoKHR presentInfo{};
      presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
      presentInfo.pSwapchains = &swapChain->swapChain;
      presentInfo.swapchainCount = 1;
      
      presentInfo.pWaitSemaphores = &GetCurrentFrame().renderSemaphore;
      presentInfo.waitSemaphoreCount = 1;
      
      presentInfo.pImageIndices = &swapChain->imageIndex;
      VkResult result = vkQueuePresentKHR(Vulkan::LogicalDevice().graphicsQueue, &presentInfo);
      if ((result == VK_ERROR_OUT_OF_DATE_KHR) || (result == VK_SUBOPTIMAL_KHR) || frameBufferResized)
      {
        frameBufferResized = false;
        swapChain->Rebuild(Renderer::GetUIPass());
        RecreateViewport();
      }
      else
      {
        CANDY_CORE_ASSERT(result == VK_SUCCESS, "failed to present swap chain image!");
      }
    }

    /*void GraphicsContext::RebuildSwapChain(VkRenderPass renderPass)
    {
      CANDY_PROFILE_FUNCTION();
      swapChain->Rebuild(renderPass);
    }*/
    
  
  void GraphicsContext::OnFrameBufferResize(Events::FrameBufferResizeEvent& event)
  {
    CANDY_PROFILE_FUNCTION();
    
    Vector2u size = {(uint32_t)event.GetWidth(), (uint32_t)event.GetHeight()};
    frameBufferResized = true;
  }
  
  /*void GraphicsContext::CleanSwapChain()
  {
    CANDY_PROFILE_FUNCTION();
      swapChain->Clean();
  }*/
  
  SwapChain& GraphicsContext::GetSwapChain()
  {
      return *swapChain;
  }
  
  uint32_t GraphicsContext::GetCurrentFrameIndex()const
  {
      return currentFrameIndex;
  }
  uint32_t GraphicsContext::GetPreviousFrameIndex()const
  {
      return previousFrameIndex;
  }
  FrameResources& GraphicsContext::GetCurrentFrame()
  {
      return frames[currentFrameIndex];
  }
  FrameResources& GraphicsContext::GetPreviousFrame()
  {
      return frames[previousFrameIndex];
  }
  FrameResources& GraphicsContext::GetFrame(uint32_t index)
  {
      return frames[index];
  }

  VkSurfaceKHR GraphicsContext::GetSurface()
  {
      return surface;
  }
  
  VkSurfaceFormatKHR GraphicsContext::GetSurfaceFormat()
  {
    CANDY_PROFILE_FUNCTION();
    SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(surface);
    return Vulkan::ChooseSwapSurfaceFormat(swapChainSupport.formats);
  }
 
  void GraphicsContext::CreateDepthResources(uint32_t frameIndex, const Math::Vector2u& size)
  {
    CANDY_PROFILE_FUNCTION();
    VkFormat depthFormat = GraphicsContext::FindDepthFormat();
    GetFrame(frameIndex).viewportData.depthImage.Create(Math::Vector2u(size.width, size.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    GetFrame(frameIndex).viewportData.depthImageView.Set(GetFrame(frameIndex).viewportData.depthImage, VK_IMAGE_ASPECT_DEPTH_BIT);
    RenderCommand::TransitionImageLayout(GetFrame(frameIndex).viewportData.depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }
  void GraphicsContext::UpdateFrameIndex()
  {
    CANDY_PROFILE_FUNCTION();
      previousFrameIndex = currentFrameIndex;
      currentFrameIndex = (currentFrameIndex + 1) % Vulkan::GetFramesInFlight();
  }
    
}