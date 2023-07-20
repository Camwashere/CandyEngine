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
      
      //deviceManager = CreateUniquePtr<VulkanDeviceManager>(surface);
      swapChain = new SwapChain(this);
      renderPass = CreateUniquePtr<RenderPass>(swapChain->imageFormat);
      InitSyncStructures();
      CreateDepthResources();
      swapChain->CreateFrameBuffers(*renderPass);
      
        //Init();
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
    }
  }
  
  void GraphicsContext::CreateDepthResources()
  {
    VkFormat depthFormat = FindDepthFormat();
    depthImage.Create(Math::Vector2u(swapChain->extent.width, swapChain->extent.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    depthImageView.Set(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    GetCurrentFrame().commandBuffer.TransitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    
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
    
  }
  
  VkRenderPassBeginInfo GraphicsContext::BeginRenderPass()
  {
      return renderPass->BeginPass(swapChain->GetCurrentFrameBuffer(), swapChain->extent);
  }

  
  
  
  FrameData& GraphicsContext::GetCurrentFrame(){return frames[currentFrameIndex];}
  


    
    

  
  
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
        //swapChain->Clean();
        
        /*for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
          vmaUnmapMemory(VulkanInstance::Allocator(), uniformBufferAllocations[i]);
          VulkanBuffer::DestroyBuffer(uniformBuffers[i], uniformBufferAllocations[i]);
        }
        vkDestroyDescriptorPool(Vulkan::LogicalDevice, descriptorPool, nullptr);
        vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice, descriptorSetLayout, nullptr);
        vertexArray->Clear();
        
        //vkDestroyPipeline(Vulkan::LogicalDevice, graphicsPipeline, nullptr);
        //vkDestroyPipelineLayout(Vulkan::LogicalDevice, pipelineLayout, nullptr);
        graphicsPipeline.Destroy();
        delete renderPass;
        for (size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++)
        {
            vkDestroySemaphore(Vulkan::LogicalDevice, imageAvailableSemaphores[i], nullptr);
            vkDestroySemaphore(Vulkan::LogicalDevice, renderFinishedSemaphores[i], nullptr);
            vkDestroyFence(Vulkan::LogicalDevice, inFlightFences[i], nullptr);
        }
      
        
        delete commandBuffer;*/
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
      }
        
        vkDestroySurfaceKHR(Vulkan::Instance(), surface, nullptr);
        
        //vkDestroyDevice(Vulkan::LogicalDevice, nullptr);
        //VulkanInstance::Shutdown();
        //vkDestroyInstance(VulkanInstance::Get(), nullptr);
    }
  
  void GraphicsContext::OnFrameBufferResize()
  {
      frameBufferResized = true;
  }
  
  void GraphicsContext::UpdateFrameIndex()
  {
    currentFrameIndex = (currentFrameIndex + 1) % FRAME_OVERLAP;
  }
    
}