#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "device/VulkanDeviceManager.hpp"
struct GLFWwindow;
namespace Candy::Graphics
{
    class GraphicsContext;
    
    class SwapChain
    {
    private:
        GraphicsContext* context;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> images;
        VkFormat imageFormat;
        VkExtent2D extent;
        std::vector<VkImageView> imageViews;
        std::vector<VkFramebuffer> frameBuffers;
        uint32_t imageIndex=0;
        
    private:
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void CreateImageViews();
        void Build();
        
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
    };
}