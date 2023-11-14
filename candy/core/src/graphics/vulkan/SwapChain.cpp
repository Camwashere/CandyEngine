#include <candy/graphics/vulkan/SwapChain.hpp>
#include <GLFW/glfw3.h>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include "candy/graphics/RenderCommand.hpp"

namespace Candy::Graphics
{
  
  SwapChain::SwapChain(GraphicsContext *gc, VkRenderPass renderPass, VkPresentModeKHR presentMode) : context(gc), preferredPresentMode(presentMode)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(Vulkan::HasDeviceManager(), "SwapChain's device manager is null!");
    CANDY_CORE_ASSERT(context->handle, "SwapChain's window handle is null!");
    CANDY_CORE_ASSERT(context->surface != VK_NULL_HANDLE, "SwapChain's surface is null!");
    imageAvailableFences.resize(Vulkan::GetFramesInFlight());
    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    //fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    fenceInfo.flags = 0;
    for (int i=0; i<imageAvailableFences.size(); i++)
    {
      CANDY_VULKAN_CHECK(vkCreateFence(Vulkan::LogicalDevice(), &fenceInfo, nullptr, &imageAvailableFences[i]));
      Vulkan::DeletionQueue().Push(imageAvailableFences[i]);
    }
    Build();
    CreateBuffers(renderPass);
  }
  
  void SwapChain::Rebuild(VkRenderPass renderPass)
  {
    CANDY_PROFILE_FUNCTION();
    int width = 0, height = 0;
    glfwGetFramebufferSize(context->handle, &width, &height);
    while (width == 0 || height == 0)
    {
      
      glfwGetFramebufferSize(context->handle, &width, &height);
      glfwWaitEvents();
    }
    vkDeviceWaitIdle(Vulkan::LogicalDevice());
    Clean();
    Build();
    CreateBuffers(renderPass);
  }
  
  void SwapChain::Clean()
  {
    CANDY_PROFILE_FUNCTION();
    Vulkan::DeletionQueue().Delete(&depthImage);
    Vulkan::DeletionQueue().Delete(&depthImageView);
    
    for (auto &buffer: buffers)
    {
      Vulkan::DeletionQueue().Delete(&buffer.frameBuffer);
      Vulkan::DeletionQueue().Delete(&buffer.view);
      
    }
    
    Vulkan::DeletionQueue().Delete(swapChain);
    
  }
  
  void SwapChain::Build()
  {
    CANDY_PROFILE_FUNCTION();
    SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(context->surface);
    VkSurfaceFormatKHR surfaceFormat = Vulkan::ChooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D swapExtent = ChooseSwapExtent(swapChainSupport.capabilities);
    
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount+1;
    if (swapChainSupport.capabilities.maxImageCount>0 && imageCount>swapChainSupport.capabilities.maxImageCount)
    {
      imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = context->surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = swapExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    QueueFamilyIndices indices = Vulkan::LogicalDevice().GetQueueFamilyIndices();
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
    
    if (indices.graphicsFamily != indices.presentFamily)
    {
      createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      createInfo.queueFamilyIndexCount = 2;
      createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
      createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
      createInfo.queueFamilyIndexCount = 0; // Optional
      createInfo.pQueueFamilyIndices = nullptr; // Optional
    }
    
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    CANDY_VULKAN_CHECK(vkCreateSwapchainKHR(Vulkan::LogicalDevice(), &createInfo, nullptr, &swapChain));
    Vulkan::DeletionQueue().Push(swapChain);
    vkGetSwapchainImagesKHR(Vulkan::LogicalDevice(), swapChain, &imageCount, nullptr);
    
    images.resize(imageCount);
    vkGetSwapchainImagesKHR(Vulkan::LogicalDevice(), swapChain, &imageCount, images.data());
    
    imageFormat = surfaceFormat.format;
    extent = swapExtent;
  }
  
  void SwapChain::CreateDepthResources()
  {
    CANDY_PROFILE_FUNCTION();
    VkFormat depthFormat = GraphicsContext::FindDepthFormat();
    depthImage.Create(Math::Vector2u(extent.width, extent.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    //depthImageView.Set(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    depthImageView.Set(depthImage, VK_IMAGE_ASPECT_DEPTH_BIT);
    
    //context->GetCurrentFrame().commandBuffer.TransitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    RenderCommand::TransitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    
  }
  
  void SwapChain::CreateBuffers(VkRenderPass renderPass)
  {
    CANDY_PROFILE_FUNCTION();
    CreateDepthResources();
    buffers.resize(images.size());
    for (size_t i = 0; i<images.size(); i++)
    {
      //buffers[i].view.Set(images[i], imageFormat);
      buffers[i].view.SetSwapChainImage(images[i], imageFormat);
      std::vector<VkImageView> attachments = {buffers[i].view, depthImageView};
      buffers[i].frameBuffer.Set(renderPass, {extent.width, extent.height}, attachments);
    }
    
    
  }
  
  
  VkResult SwapChain::AcquireNextImage(VkSemaphore semaphore, uint64_t timeout)
  {
    CANDY_PROFILE_FUNCTION();
    return vkAcquireNextImageKHR(Vulkan::LogicalDevice(), swapChain, timeout, semaphore, imageAvailableFences[context->GetCurrentFrameIndex()], &imageIndex);
  }
  
  void SwapChain::SetPreferredPresentMode(VkPresentModeKHR mode)
  {
    preferredPresentMode = mode;
  }
  VkPresentModeKHR SwapChain::GetPreferredPresentMode()const
  {
    return preferredPresentMode;
  }
  
  FrameBuffer &SwapChain::GetCurrentFrameBuffer()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_VULKAN_CHECK(vkWaitForFences(Vulkan::LogicalDevice(), 1, &imageAvailableFences[context->GetCurrentFrameIndex()], VK_TRUE, UINT64_MAX));
    CANDY_VULKAN_CHECK(vkResetFences(Vulkan::LogicalDevice(), 1, &imageAvailableFences[context->GetCurrentFrameIndex()]));
    return buffers[imageIndex].frameBuffer;
  }
  
  
  VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
  {
    CANDY_PROFILE_FUNCTION();
    for (const auto &availablePresentMode: availablePresentModes)
    {
      if (availablePresentMode == preferredPresentMode)
      {
        return availablePresentMode;
      }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
  }
  
  VulkanImageView &SwapChain::GetCurrentImageView()
  {
    return buffers[imageIndex].view;
  }
  
  VkImage SwapChain::GetCurrentImage()
  {
    return images[imageIndex];
  }
  
  VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
  {
    CANDY_PROFILE_FUNCTION();
    if (capabilities.currentExtent.width != Math::Limit<uint32_t>::Max())
    {
      return capabilities.currentExtent;
    }
    else
    {
      int width, height;
      glfwGetFramebufferSize(context->handle, &width, &height);
      
      VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
      
      actualExtent.width = Math::Clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
      actualExtent.height = Math::Clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
      
      return actualExtent;
    }
  }
}