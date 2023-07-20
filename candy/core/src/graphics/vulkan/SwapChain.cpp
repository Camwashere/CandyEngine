#include <candy/graphics/vulkan/SwapChain.hpp>
#include <GLFW/glfw3.h>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Vulkan.hpp>

namespace Candy::Graphics
{
    SwapChain::SwapChain(GraphicsContext* gc) : context(gc)
    {
        CANDY_CORE_ASSERT(Vulkan::HasDeviceManager(), "SwapChain's device manager is null!");
        CANDY_CORE_ASSERT(context->handle, "SwapChain's window handle is null!");
        CANDY_CORE_ASSERT(context->surface != VK_NULL_HANDLE, "SwapChain's surface is null!");
        Build();
        CreateImageViews();
    }
    
    void SwapChain::Rebuild(VkRenderPass renderPass)
    {
        int width = 0, height = 0;
        glfwGetFramebufferSize(context->handle, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(context->handle, &width, &height);
            glfwWaitEvents();
        }
        vkDeviceWaitIdle(Vulkan::LogicalDevice());
        Clean();
        Build();
        CreateImageViews();
        CreateFrameBuffers(renderPass);
    }
    
    void SwapChain::Clean()
    {
      depthImageView.Destroy();
      depthImage.Destroy();
        for (auto & swapChainFrameBuffer : frameBuffers) {
            vkDestroyFramebuffer(Vulkan::LogicalDevice(), swapChainFrameBuffer, nullptr);
        }
        
        for (auto & swapChainImageView : imageViews) {
          swapChainImageView.Destroy();
        }
        
        vkDestroySwapchainKHR(Vulkan::LogicalDevice(), swapChain, nullptr);
    }
    
    void SwapChain::Build()
    {
        SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(context->surface);
        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D swapExtent = ChooseSwapExtent(swapChainSupport.capabilities);
        
        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
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
        
        QueueFamilyIndices indices = Vulkan::PhysicalDevice().FindQueueFamilies(context->surface);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        
        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0; // Optional
            createInfo.pQueueFamilyIndices = nullptr; // Optional
        }
        
        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;
        CANDY_CORE_ASSERT(vkCreateSwapchainKHR(Vulkan::LogicalDevice(), &createInfo, nullptr, &swapChain) == VK_SUCCESS, "Failed to create swap chain!");
        vkGetSwapchainImagesKHR(Vulkan::LogicalDevice(), swapChain, &imageCount, nullptr);
        images.resize(imageCount);
        vkGetSwapchainImagesKHR(Vulkan::LogicalDevice(), swapChain, &imageCount, images.data());
        
        imageFormat = surfaceFormat.format;
        extent = swapExtent;
    }
  void SwapChain::CreateDepthResources()
  {
    VkFormat depthFormat = GraphicsContext::FindDepthFormat();
    depthImage.Create(Math::Vector2u(extent.width, extent.height), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT);
    depthImageView.Set(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    context->GetCurrentFrame().commandBuffer.TransitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    
  }
    void SwapChain::CreateImageViews()
    {
        imageViews.resize(images.size());
        
        for (size_t i = 0; i < images.size(); i++) {
          imageViews[i].Set(images[i], imageFormat);
          
            
        }
    }
    
    void SwapChain::CreateFrameBuffers(VkRenderPass renderPass)
    {
      CreateDepthResources();
        frameBuffers.resize(imageViews.size());
        for (size_t i = 0; i < imageViews.size(); i++)
        {
          std::array<VkImageView, 2> attachments = {imageViews[i], depthImageView};
            
            
            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = extent.width;
            framebufferInfo.height = extent.height;
            framebufferInfo.layers = 1;
            
            CANDY_CORE_ASSERT(vkCreateFramebuffer(Vulkan::LogicalDevice(), &framebufferInfo, nullptr, &frameBuffers[i]) == VK_SUCCESS, "Failed to create framebuffer");
            
        }
    }
  
  VkResult SwapChain::AcquireNextImage(VkSemaphore semaphore, uint64_t timeout, VkFence fence)
  {
    return vkAcquireNextImageKHR(Vulkan::LogicalDevice(), swapChain, timeout, semaphore, fence, &imageIndex);
  }
  
  VkFramebuffer SwapChain::GetCurrentFrameBuffer(){return frameBuffers[imageIndex];}
    
    VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }
    
    VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
            {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }
    
    VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        
        if (capabilities.currentExtent.width != Math::Limit<uint32_t>::Max()) {
            return capabilities.currentExtent;
        } else {
            int width, height;
            glfwGetFramebufferSize(context->handle, &width, &height);
            
            VkExtent2D actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
            };
            
            actualExtent.width = Math::Clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
            actualExtent.height = Math::Clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
            
            return actualExtent;
        }
    }
}