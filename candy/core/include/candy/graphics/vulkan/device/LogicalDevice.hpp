#pragma once
#include "PhysicalDevice.hpp"
namespace Candy::Graphics
{
    
    
    class LogicalDevice
    {
    public:
        VkDevice device=VK_NULL_HANDLE;
        VkQueue graphicsQueue = VK_NULL_HANDLE;
        VkQueue presentQueue = VK_NULL_HANDLE;
    
    
    public:
        LogicalDevice()=default;
        explicit LogicalDevice(const PhysicalDevice& physicalDevice, const QueueFamilyIndices& indices);
        
        
    public:
        operator VkDevice(){return device;}
        operator VkDevice()const{return device;}
        
    private:
        friend class GraphicsContext;
        friend class CommandBuffer;
        friend class Renderer;
        
        
    };
}