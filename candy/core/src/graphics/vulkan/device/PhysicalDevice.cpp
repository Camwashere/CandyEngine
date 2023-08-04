#include <candy/graphics/vulkan/device/PhysicalDevice.hpp>
#include <set>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <string>
namespace Candy::Graphics
{
    
    PhysicalDevice::PhysicalDevice() : device(VK_NULL_HANDLE)
    {
      //vkGetPhysicalDeviceProperties(device, &properties);
    
    }
    PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : device(physicalDevice)
    {
      vkGetPhysicalDeviceProperties(device, &properties);
    }
    PhysicalDevice::PhysicalDevice(const PhysicalDevice& other) = default;
    
    
    bool PhysicalDevice::IsValid()const{return device != VK_NULL_HANDLE;}
    
    QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkSurfaceKHR surface)
    {
        return FindQueueFamilies(device, surface);
    }
    
    SwapChainSupportDetails PhysicalDevice::QuerySwapChainSupport(VkSurfaceKHR surface)
    {
        return QuerySwapChainSupport(device, surface);
    }
    
    bool PhysicalDevice::IsDeviceSuitable(VkSurfaceKHR surface)
    {
        return IsDeviceSuitable(device, surface);
    }
    
    bool PhysicalDevice::CheckDeviceExtensionSupport()
    {
        return CheckExtensionSupport(device);
    }
    
    bool PhysicalDevice::CheckExtensionSupport(VkPhysicalDevice device)
    {
      
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
        
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
        
        std::set<std::string> requiredExtensions(VulkanDeviceManager::DEVICE_EXTENSIONS.begin(), VulkanDeviceManager::DEVICE_EXTENSIONS.end());
        
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }
        
        return requiredExtensions.empty();
    }
    
    bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices = FindQueueFamilies(device, surface);
        
        bool extensionsSupported = CheckExtensionSupport(device);
        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }
        
        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
        return indices.IsComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }
    
    SwapChainSupportDetails PhysicalDevice::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
        SwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
        
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
        
        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
        
        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }
        
        return details;
    }
    QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
    {
        QueueFamilyIndices indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        
        // Find at least one queue family that supports VK_QUEUE_GRAPHICS_BIT
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            if (presentSupport)
            {
                indices.presentFamily = i;
            }
            if (indices.IsComplete())
            {
                break;
            }
            i++;
        }
        
        return indices;
    }
  
  const char* PhysicalDevice::GetName()const
  {
      return properties.deviceName;
  }
  uint32_t PhysicalDevice::GetDriverVersion()const
  {
      return properties.driverVersion;
  }
  uint32_t PhysicalDevice::GetApiVersion()const
  {
    return properties.apiVersion;
  }
  uint32_t PhysicalDevice::GetVendorID()const
  {
      return properties.vendorID;
  }
  uint32_t PhysicalDevice::GetDeviceID()const
  {
      return properties.deviceID;
  }
  size_t PhysicalDevice::GetMinUniformBufferOffsetAlignment()const
  {
      return properties.limits.minUniformBufferOffsetAlignment;
  }
  uint32_t PhysicalDevice::GetMaxPushConstantSize()const
  {
      return properties.limits.maxPushConstantsSize;
  }
  uint32_t PhysicalDevice::GetMaxDynamicUniformBufferCount()const
  {
    return properties.limits.maxDescriptorSetUniformBuffersDynamic;
  }
  
  uint32_t PhysicalDevice::GetMaxUniformBufferSize()const
  {
      return properties.limits.maxUniformBufferRange;
  }
  
  size_t PhysicalDevice::PadUniformBufferSize(size_t originalSize)const
  {
    size_t minUboAlignment = GetMinUniformBufferOffsetAlignment();
    size_t alignedSize = originalSize;
    if (minUboAlignment > 0)
    {
      alignedSize = (alignedSize + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }
    return alignedSize;
  }
}