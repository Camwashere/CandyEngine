#pragma once
#include "PhysicalDevice.hpp"
namespace Candy::Graphics
{
  
  struct QueueFamilyIndices
  {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> computeFamily;
    std::optional<uint32_t> transferFamily;
    
    [[nodiscard]] bool IsComplete() const
    {
      return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value() && transferFamily.has_value();
    }
  };
    class LogicalDevice
    {
    
    private:
      QueueFamilyIndices queueFamilyIndices;
      void FindQueueFamilies(VkSurfaceKHR surface);
    public:
      PhysicalDevice* physicalDevice;
      
        VkDevice device=VK_NULL_HANDLE;
        VkQueue graphicsQueue = VK_NULL_HANDLE;
        VkQueue presentQueue = VK_NULL_HANDLE;
        VkQueue computeQueue = VK_NULL_HANDLE;
        VkQueue transferQueue = VK_NULL_HANDLE;
    
    
    public:
        //LogicalDevice()=default;
        explicit LogicalDevice(PhysicalDevice* physicalDevice, VkSurfaceKHR surface);
        
        QueueFamilyIndices GetQueueFamilyIndices()const;
        
        
    public:
        operator VkDevice(){return device;}
        operator VkDevice()const{return device;}
        
    private:
        friend class GraphicsContext;
        friend class CommandBuffer;
        friend class Renderer;
        
        
    };
}