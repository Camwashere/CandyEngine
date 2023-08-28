#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
#include "Image.hpp"
#include "ImageView.hpp"
#include "../FrameBuffer.hpp"

struct GLFWwindow;
namespace Candy::Graphics
{
  class GraphicsContext;
  
  struct SwapChainBuffer
  {
    ImageView view;
    FrameBuffer frameBuffer;
  };
  
  class SwapChain
  {
  private:
    GraphicsContext *context;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> images;
    std::vector<SwapChainBuffer> buffers;
    VkFormat imageFormat;
    VkExtent2D extent;
    Image depthImage;
    ImageView depthImageView;
    VkPresentModeKHR preferredPresentMode;
    uint32_t imageIndex = 0;
  
  private:
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    void Build();
    void CreateDepthResources();
    void CreateBuffers(VkRenderPass renderPass);
  
  public:
    explicit SwapChain(GraphicsContext *context, VkRenderPass renderPass, VkPresentModeKHR preferredPresentMode = VK_PRESENT_MODE_MAILBOX_KHR);
  
  public:
    operator VkSwapchainKHR() {return swapChain;}
    operator VkSwapchainKHR() const {return swapChain;}
  
  public:
    void Rebuild(VkRenderPass renderPass);
    void Clean();
    VkResult AcquireNextImage(VkSemaphore semaphore, uint64_t timeout = UINT64_MAX, VkFence fence = nullptr);
    void SetPreferredPresentMode(VkPresentModeKHR mode);
    VkPresentModeKHR GetPreferredPresentMode()const;
    FrameBuffer &GetCurrentFrameBuffer();
    ImageView &GetCurrentImageView();
    VkImage GetCurrentImage();
  
  private:
    friend class GraphicsContext;
    friend class Renderer;
    friend class Vulkan;
  };
}