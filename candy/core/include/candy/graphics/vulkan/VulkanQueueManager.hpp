#pragma once
#include <vulkan/vulkan.h>
#include <optional>
#include <candy/base/Base.hpp>
#include <vector>
namespace Candy::Graphics
{
  
  
  struct QueueFamilyIndices
  {
    std::optional <uint32_t> graphicsFamily;
    std::optional <uint32_t> presentFamily;
    std::optional <uint32_t> computeFamily;
    std::optional <uint32_t> transferFamily;
    
    [[nodiscard]] bool IsComplete() const
    {
      return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value() && transferFamily.has_value();
    }
  };
  
  

  
  class VulkanQueueManager
  {
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
  
  };
}

