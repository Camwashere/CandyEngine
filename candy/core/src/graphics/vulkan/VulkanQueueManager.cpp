#include <candy/graphics/vulkan/VulkanQueueManager.hpp>
#include "CandyPch.hpp"
namespace Candy::Graphics
{
  
  
  QueueFamilyIndices VulkanQueueManager::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    VkBool32 presentSupport = false;
    
    std::vector<uint32_t> graphicsIndices;
    std::vector<uint32_t> presentIndices;
    std::vector<uint32_t> computeIndices;
    std::vector<uint32_t> transferIndices;
    
    // Find all queue families that support required operations
    for (uint32_t i = 0; i<queueFamilyCount; i++)
    {
      if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
        graphicsIndices.push_back(i);
      }
      if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
      {
        computeIndices.push_back(i);
      }
      if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
      {
        transferIndices.push_back(i);
      }
      
      vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
      if (presentSupport)
      {
        presentIndices.push_back(i);
      }
    }
    return indices;
  }
}