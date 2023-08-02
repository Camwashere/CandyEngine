#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
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
        GraphicsContext* context;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> images;
        std::vector<SwapChainBuffer> buffers;
        VkFormat imageFormat;
        VkExtent2D extent;
        Image depthImage;
        ImageView depthImageView;
        uint32_t imageIndex=0;
        
    private:
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void Build();
        void CreateDepthResources();
        
    public:
        explicit SwapChain(GraphicsContext* context, VkRenderPass renderPass);
        
    public:
        operator VkSwapchainKHR(){return swapChain;}
        operator VkSwapchainKHR()const{return swapChain;}
        
    public:
        void Rebuild(VkRenderPass renderPass);
        void Clean();
        void CreateBuffers(VkRenderPass renderPass);
        VkResult AcquireNextImage(VkSemaphore semaphore, uint64_t timeout=UINT64_MAX, VkFence fence=nullptr);
        FrameBuffer& GetCurrentFrameBuffer();
        ImageView& GetCurrentImageView();
        VkImage GetCurrentImage();
    private:
        friend class GraphicsContext;
        friend class Renderer;
        friend class Vulkan;
    };
}