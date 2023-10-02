#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  
  
  
    VulkanDeviceManager::VulkanDeviceManager(VkSurfaceKHR surface) : physicalDevice(surface)
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(physicalDevice.IsValid(), "Failed to find a suitable GPU!");
      logicalDevice = LogicalDevice(physicalDevice, physicalDevice.FindQueueFamilies(surface));
    }
  
  void VulkanDeviceManager::Destroy()
  {
    CANDY_PROFILE_FUNCTION();
      vkDeviceWaitIdle(logicalDevice);
      vkDestroyDevice(logicalDevice, nullptr);
  }
    
    
    
    
    
   
    
    
    
    
    
    
}