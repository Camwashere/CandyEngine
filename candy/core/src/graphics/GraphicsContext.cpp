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
        frames[i].viewportData.viewportDescriptor = ImGui_ImplVulkan_AddTexture(viewportTarget.imageResources[0].imageView.GetSampler(), viewportTarget.imageResources[0].imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        frames[i].viewportData.viewportDepthDescriptor = ImGui_ImplVulkan_AddTexture(viewportTarget.imageResources[1].imageView.GetSampler(), viewportTarget.imageResources[1].imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      }
  }
  void GraphicsContext::CreateViewport()
  {
    CANDY_PROFILE_FUNCTION();
    Vector2u size = {swapChain->extent.width, swapChain->extent.height};
    VkFormat depthFormat = GraphicsContext::FindDepthFormat();
    
    
    viewportTarget.imageResources.resize(2);
    selectionTarget.imageResources.resize(1);
    
    viewportTarget.imageResources[0].image.Create(size, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    viewportTarget.imageResources[0].imageView.Set(viewportTarget.imageResources[0].image);
    
    viewportTarget.imageResources[1].image.Create(Math::Vector2u(size.width, size.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    viewportTarget.imageResources[1].imageView.Set(viewportTarget.imageResources[1].image, VK_IMAGE_ASPECT_DEPTH_BIT);
    
    
    
    selectionTarget.imageResources[0].image.Create(size, VK_FORMAT_R32_SINT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    selectionTarget.imageResources[0].imageView.Set(selectionTarget.imageResources[0].image);
    
    viewportTarget.frameBuffer.Set(Renderer::GetViewportPass(), size, {viewportTarget.imageResources[0].imageView, viewportTarget.imageResources[1].imageView});
    selectionTarget.frameBuffer.Set(Renderer::GetSelectionPass(), size, {selectionTarget.imageResources[0].imageView, viewportTarget.imageResources[1].imageView});
    
    RenderCommand::TransitionImageLayout(viewportTarget.imageResources[0].image, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    RenderCommand::TransitionImageLayout(selectionTarget.imageResources[0].image, VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    RenderCommand::TransitionImageLayout(viewportTarget.imageResources[1].image, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    
    selectionPixelBuffer = new PixelBuffer(size);
  }
  
  void GraphicsContext::CleanViewport()
  {
    CANDY_PROFILE_FUNCTION();
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[1].image);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[1].imageView);
    
    Vulkan::DeletionQueue().Delete(&selectionTarget.frameBuffer);
    Vulkan::DeletionQueue().Delete(&selectionTarget.imageResources[0].image);
    Vulkan::DeletionQueue().Delete(&selectionTarget.imageResources[0].imageView);
    
    Vulkan::DeletionQueue().Delete(selectionPixelBuffer);
    delete selectionPixelBuffer;
    
    Vulkan::DeletionQueue().Delete(&viewportTarget.frameBuffer);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[0].image);
    Vulkan::DeletionQueue().Delete(&viewportTarget.imageResources[0].imageView);
   
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

    
  
  void GraphicsContext::OnFrameBufferResize(Events::FrameBufferResizeEvent& event)
  {
    CANDY_PROFILE_FUNCTION();
    
    Vector2u size = {(uint32_t)event.GetWidth(), (uint32_t)event.GetHeight()};
    frameBufferResized = true;
  }
  
  
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
  
  void GraphicsContext::UpdateFrameIndex()
  {
    CANDY_PROFILE_FUNCTION();
      previousFrameIndex = currentFrameIndex;
      currentFrameIndex = (currentFrameIndex + 1) % Vulkan::GetFramesInFlight();
  }
    
}