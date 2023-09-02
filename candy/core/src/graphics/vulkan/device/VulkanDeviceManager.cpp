#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
    
    VulkanDeviceManager::VulkanDeviceManager(VkSurfaceKHR surface)
    {
      uint32_t deviceCount=0;
      vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, nullptr);
      CANDY_CORE_ASSERT(deviceCount, "Failed to find GPUs with Vulkan support!");
      std::vector<VkPhysicalDevice> devices(deviceCount);
      vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, devices.data());
      for (const auto& device : devices)
      {
        if (PhysicalDevice::IsDeviceSuitable(device, surface))
        {
          physicalDevice = PhysicalDevice(device);
          break;
        }
      }
      CANDY_CORE_ASSERT(physicalDevice.IsValid(), "Failed to find a suitable GPU!");
      
      logicalDevice = LogicalDevice(physicalDevice, physicalDevice.FindQueueFamilies(surface));
      //ClearDeviceMemory();
    }
  
  void VulkanDeviceManager::Destroy()
  {
      vkDeviceWaitIdle(logicalDevice);
      vkDestroyDevice(logicalDevice, nullptr);
  }
    
    
    
    
    
   
    
    
    
    
    
    
}