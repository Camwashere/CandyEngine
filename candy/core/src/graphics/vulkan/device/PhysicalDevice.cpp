#include <candy/graphics/vulkan/device/PhysicalDevice.hpp>
#include <set>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <string>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  
  struct ScoredDevice
  {
    long long int score;
    VkPhysicalDevice device;
  };
  static std::vector<ScoredDevice> RankSuitableDevices(VkSurfaceKHR surface, const std::vector<VkPhysicalDevice>& foundDevices)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<ScoredDevice> scoredDevices;
    for (auto d : foundDevices)
    {
      ScoredDevice sd{PhysicalDevice::RateDeviceSuitability(d, surface), d};
      
      if (sd.score > 0)
      {
        scoredDevices.push_back(sd);
      }
    }
    
    std::sort(scoredDevices.begin(), scoredDevices.end(), [](const ScoredDevice& a, const ScoredDevice& b){return a.score > b.score;});
    
    return scoredDevices;
  }
  
  PhysicalDevice::PhysicalDevice(VkSurfaceKHR surface) : device(VK_NULL_HANDLE)
  {
    CANDY_PROFILE_FUNCTION();
    
    uint32_t deviceCount=0;
    vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, nullptr);
    CANDY_CORE_ASSERT(deviceCount, "Failed to find GPUs with Vulkan support!");
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, devices.data());
    
    std::vector<ScoredDevice> scoredDevices = RankSuitableDevices(surface, devices);
    
    CANDY_CORE_ASSERT(!scoredDevices.empty(), "Failed to find a suitable GPU!");
    int64_t currentScore = -1;
    for (const auto& d : scoredDevices)
    {
      CANDY_CORE_INFO("Found GPU with score {0}", d.score);
      
      if (d.score == currentScore)
      {
        CANDY_CORE_ASSERT(false, "Found multiple GPUs with the same score!");
      }
    }
    
    device = scoredDevices[0].device;
    
    vkGetPhysicalDeviceProperties(device, &properties);
    
    vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);
    maxAllocationSize=0;
    for (uint32_t i=0; i<memoryProperties.memoryHeapCount; i++)
    {
      if (memoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
      {
        maxAllocationSize = memoryProperties.memoryHeaps[i].size;
        break;
      }
    }
    CANDY_CORE_ASSERT(maxAllocationSize>0, "Failed to find a suitable GPU!");
    
    name = properties.deviceName;
    CANDY_CORE_INFO("Using GPU: {0}", name);
    
  }
  
  
  /*PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : device(physicalDevice)
  {
    vkGetPhysicalDeviceProperties(device, &properties);
    
    vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);
    maxAllocationSize=0;
    for (uint32_t i=0; i<memoryProperties.memoryHeapCount; i++)
    {
      if (memoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
      {
        maxAllocationSize = memoryProperties.memoryHeaps[i].size;
        break;
      }
    }
    CANDY_CORE_ASSERT(maxAllocationSize>0, "Failed to find a suitable GPU!");
  }*/
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
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    QueueFamilyIndices indices = FindQueueFamilies(device, surface);
    
    bool extensionsSupported = CheckExtensionSupport(device);
    
    if (extensionsSupported)
    {
      SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
      bool swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
      
      VkPhysicalDeviceShaderDrawParametersFeatures parametersFeatures{};
      
      parametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
      VkPhysicalDeviceFeatures2 supportedFeatures;
      supportedFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
      supportedFeatures.pNext = &parametersFeatures;
      vkGetPhysicalDeviceFeatures2(device, &supportedFeatures);
      
      
      
      return indices.IsComplete() && swapChainAdequate && supportedFeatures.features.samplerAnisotropy && parametersFeatures.shaderDrawParameters;
    }
    return false;
    
    
  }
  
  long long int PhysicalDevice::RateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    if (! IsDeviceSuitable(device, surface))
    {
      return -1;
    }
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    long long int score=0;
    
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
      score += 1000;
    }
    score += deviceProperties.limits.maxMemoryAllocationCount;
    score += deviceProperties.limits.maxImageDimension2D;
    score += deviceProperties.limits.maxBoundDescriptorSets;
    score += deviceProperties.limits.maxStorageBufferRange;
    score += deviceProperties.limits.maxComputeSharedMemorySize;
    CANDY_CORE_INFO("Device {0} scored {1}", deviceProperties.deviceName, score);
    return score;
  }
  
  SwapChainSupportDetails PhysicalDevice::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
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
  size_t PhysicalDevice::GetMaxAllocationSize()const
  {
    return maxAllocationSize;
  }
  VkPhysicalDeviceProperties PhysicalDevice::GetProperties()const
  {
    
    return properties;
  }
  
  size_t PhysicalDevice::PadUniformBufferSize(size_t originalSize)const
  {
    CANDY_PROFILE_FUNCTION();
    size_t minUboAlignment = GetMinUniformBufferOffsetAlignment();
    size_t alignedSize = originalSize;
    if (minUboAlignment > 0)
    {
      alignedSize = (alignedSize + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }
    return alignedSize;
  }
}