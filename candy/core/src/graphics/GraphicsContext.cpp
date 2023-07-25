#include <candy/graphics/GraphicsContext.hpp>
#include <CandyPch.hpp>
#include <GLFW/glfw3.h>
#include <set>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
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
      frames[i].uniformBuffer = CreateSharedPtr<UniformBuffer>(192);
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
      
      
      
      CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
      
      
    }
    
    void GraphicsContext::RebuildSwapChain()
    {
      swapChain->Rebuild(*renderPass);
    }
    
    void GraphicsContext::Terminate()
    {
        vkDeviceWaitIdle(Vulkan::LogicalDevice());
       
      renderPass->Destroy();
      for (size_t i=0; i<FRAME_OVERLAP; i++)
      {
        
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].renderSemaphore, nullptr);
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].presentSemaphore, nullptr);
        vkDestroyFence(Vulkan::LogicalDevice(), frames[i].renderFence, nullptr);
      }
      
      for (size_t i=0; i<FRAME_OVERLAP; i++)
      {
        frames[i].commandBuffer.Destroy();
        frames[i].uniformBuffer->Destroy();
      }
        
        vkDestroySurfaceKHR(Vulkan::Instance(), surface, nullptr);
        
      
    }
  
  void GraphicsContext::OnFrameBufferResize()
  {
      frameBufferResized = true;
  }
  FrameData& GraphicsContext::GetCurrentFrame()
  {
      return frames[currentFrameIndex];
  }
  FrameData& GraphicsContext::GetPreviousFrame()
  {
      return frames[previousFrameIndex];
  }
  void GraphicsContext::UpdateFrameIndex()
  {
      previousFrameIndex = currentFrameIndex;
      currentFrameIndex = (currentFrameIndex + 1) % FRAME_OVERLAP;
  }
    
}