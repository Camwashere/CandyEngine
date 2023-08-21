#pragma once

#include "LogicalDevice.hpp"
#include "PhysicalDevice.hpp"
#include <vector>
namespace Candy::Graphics
{
    class VulkanDeviceManager
    {
    public:
        static inline const std::vector<const char*> DEVICE_EXTENSIONS = {VK_KHR_SWAPCHAIN_EXTENSION_NAME, VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME};
        
    public:
        PhysicalDevice physicalDevice;
        LogicalDevice logicalDevice;
        
    public:
        explicit VulkanDeviceManager(VkSurfaceKHR surface);
        
    public:
      void ClearDeviceMemory();
      void Destroy();
        
    private:
        friend class GraphicsContext;
        friend class SwapChain;
        
        
    
        
    };
}