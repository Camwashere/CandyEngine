#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
#include "ImageView.hpp"
struct GLFWwindow;
namespace Candy::Graphics
{
    class GraphicsContext;
    struct SwapChainBuffer
    {
      VkImage image;
      VkImageView view;
      VkFramebuffer frameBuffer;
    };
    class SwapChain
    {
    private:
        GraphicsContext* context;
        VkSwapchainKHR swapChain;
        //VkSurfaceFormatKHR surfaceFormat;
        //SwapChainSupportDetails swapChainSupport;
        std::vector<VkImage> images;
        VkFormat imageFormat;
        VkExtent2D extent;
        //std::vector<SwapChainBuffer> buffers;
        std::vector<ImageView> imageViews;
        std::vector<VkFramebuffer> frameBuffers;
        Image depthImage;
        ImageView depthImageView;
        uint32_t imageIndex=0;
        
    private:
        //VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void CreateImageViews();
        void Build();
        void CreateDepthResources();
        
    public:
        explicit SwapChain(GraphicsContext* context);
        
    public:
        operator VkSwapchainKHR(){return swapChain;}
        operator VkSwapchainKHR()const{return swapChain;}
        
    public:
        void Rebuild(VkRenderPass renderPass);
        void Clean();
        void CreateFrameBuffers(VkRenderPass renderPass);
        VkResult AcquireNextImage(VkSemaphore semaphore, uint64_t timeout=UINT64_MAX, VkFence fence=nullptr);
        VkFramebuffer GetCurrentFrameBuffer();
    private:
        friend class GraphicsContext;
        friend class Renderer;
        friend class Vulkan;
    };
}