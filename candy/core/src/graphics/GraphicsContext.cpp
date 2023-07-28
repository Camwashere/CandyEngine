#include <candy/graphics/GraphicsContext.hpp>
#include <CandyPch.hpp>
#include <GLFW/glfw3.h>
#include <set>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
    GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
    {
      handle = windowHandle;
      CANDY_CORE_ASSERT(glfwCreateWindowSurface(Vulkan::Instance(), windowHandle, nullptr, &surface) == VK_SUCCESS, "Failed to create vulkan window surface!");
      Vulkan::InitDeviceManager(surface);
      
      swapChain = new SwapChain(this);
      renderPass = CreateUniquePtr<RenderPass>(swapChain->imageFormat);
      InitSyncStructures();
      swapChain->CreateFrameBuffers(*renderPass);
      Vulkan::RegisterContext(this);
    }
  void GraphicsContext::InitSyncStructures()
  {
    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    
    
    
    
    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    
    for (int i = 0; i < FRAME_OVERLAP; i++) {
      frames[i].commandBuffer.Init(surface);
      CANDY_CORE_ASSERT(vkCreateFence(Vulkan::LogicalDevice(), &fenceCreateInfo, nullptr, &frames[i].renderFence)==VK_SUCCESS);
      CANDY_CORE_ASSERT(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].presentSemaphore)==VK_SUCCESS);
      CANDY_CORE_ASSERT(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].renderSemaphore)==VK_SUCCESS);
      frames[i].uniformBuffer = UniformBuffer::Create(Vulkan::PhysicalDevice().PadUniformBufferSize(sizeof(Color))*FRAME_OVERLAP);
    }
  }
  

  
  bool GraphicsContext::HasStencilComponent(VkFormat format)
  {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
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
  
  VkRenderPassBeginInfo GraphicsContext::BeginRenderPass()
  {
      return renderPass->BeginPass(swapChain->GetCurrentFrameBuffer(), swapChain->extent);
  }

  
  
  
  


    
    

  
  
    void GraphicsContext::SwapBuffers()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(vkWaitForFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence, true, UINT64_MAX) == VK_SUCCESS);
      
      VkResult result = swapChain->AcquireNextImage(GetCurrentFrame().presentSemaphore, UINT64_MAX);
      
      if (result == VK_ERROR_OUT_OF_DATE_KHR)
      {
        frameBufferResized = false;
        swapChain->Rebuild(*renderPass);
      }
      else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
      {
        CANDY_CORE_ASSERT(false, "Failed to acquire swap chain image!");
      }
      
      
      
      //CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
      
      
      
      
    }
    
    void GraphicsContext::Present()
    {
      VkPresentInfoKHR presentInfo{};
      presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
      presentInfo.pSwapchains = &swapChain->swapChain;
      presentInfo.swapchainCount = 1;
      
      presentInfo.pWaitSemaphores = &GetCurrentFrame().renderSemaphore;
      presentInfo.waitSemaphoreCount = 1;
      
      presentInfo.pImageIndices = &swapChain->imageIndex;
      
      VkResult result = vkQueuePresentKHR(Vulkan::LogicalDevice().graphicsQueue, &presentInfo);
      if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
      {
        swapChain->Rebuild(*renderPass);
      }
      else
      {
        CANDY_CORE_ASSERT(result == VK_SUCCESS, "failed to present swap chain image!");
      }
      //descriptorAllocator.Flip();
      
      UpdateFrameIndex();
    }
    
    void GraphicsContext::RebuildSwapChain()
    {
      swapChain->Rebuild(*renderPass);
    }
    
    void GraphicsContext::Terminate()
    {
        vkDeviceWaitIdle(Vulkan::LogicalDevice());
       //renderPass.reset();
      renderPass->Destroy();
      for (size_t i=0; i<FRAME_OVERLAP; i++)
      {
        
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].renderSemaphore, nullptr);
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].presentSemaphore, nullptr);
        vkDestroyFence(Vulkan::LogicalDevice(), frames[i].renderFence, nullptr);
        frames[i].uniformBuffer->Destroy();
        frames[i].commandBuffer.Destroy();
        
      }
      
        swapChain->Clean();
        vkDestroySurfaceKHR(Vulkan::Instance(), surface, nullptr);
      
      //CANDY_CORE_INFO("DESTROYED GRAPHICS CONTEXT");
        
      
    }
  
  void GraphicsContext::OnFrameBufferResize()
  {
      frameBufferResized = true;
  }
  
  void GraphicsContext::CleanSwapChain()
  {
      swapChain->Clean();
  }
  
  uint32_t GraphicsContext::GetCurrentFrameIndex()const
  {
      return currentFrameIndex;
  }
  uint32_t GraphicsContext::GetPreviousFrameIndex()const
  {
      return previousFrameIndex;
  }
  FrameData& GraphicsContext::GetCurrentFrame()
  {
      return frames[currentFrameIndex];
  }
  FrameData& GraphicsContext::GetPreviousFrame()
  {
      return frames[previousFrameIndex];
  }
  FrameData& GraphicsContext::GetFrame(uint32_t index)
  {
      return frames[index];
  }
  VkRenderPass GraphicsContext::GetRenderPass()
  {
      return *renderPass;
  }
  VkSurfaceKHR GraphicsContext::GetSurface()
  {
      return surface;
  }
  void GraphicsContext::UpdateFrameIndex()
  {
      previousFrameIndex = currentFrameIndex;
      currentFrameIndex = (currentFrameIndex + 1) % FRAME_OVERLAP;
  }
    
}