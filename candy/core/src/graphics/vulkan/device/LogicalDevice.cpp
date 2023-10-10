#include <candy/graphics/vulkan/device/LogicalDevice.hpp>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <set>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/VulkanDebugManager.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <unordered_map>
namespace Candy::Graphics
{
  
  
  
  LogicalDevice::LogicalDevice(PhysicalDevice* physicalDevicePtr, VkSurfaceKHR surface) : physicalDevice(physicalDevicePtr)
  {
    CANDY_PROFILE_FUNCTION();
    FindQueueFamilies(surface);
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    
    std::set<uint32_t> uniqueQueueFamilies = {queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value(), queueFamilyIndices.computeFamily.value(), queueFamilyIndices.transferFamily.value()};
    std::unordered_map<uint32_t, std::vector<float> > queuePriorities{};
    std::vector<uint32_t> queueIndices{};
    std::unordered_map<uint32_t, uint32_t> queueCounts{};
    queueIndices.push_back(queueCounts[queueFamilyIndices.graphicsFamily.value()]);
    queueIndices.push_back(queueCounts[queueFamilyIndices.graphicsFamily.value()]);
    queueIndices.push_back(queueCounts[queueFamilyIndices.computeFamily.value()]++);
    queueIndices.push_back(queueCounts[queueFamilyIndices.transferFamily.value()]++);
    for (uint32_t queueFamily: uniqueQueueFamilies)
    {
      VkDeviceQueueCreateInfo queueCreateInfo{};
      queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueCreateInfo.queueFamilyIndex = queueFamily;
      
      std::vector<float>& priorities = queuePriorities[queueFamily];
      //priorities.push_back(1.0f); // Push a new priority for each new queue
      
      queueCreateInfo.queueCount = queueCounts[queueFamily];
      for (int i=0; i<queueCreateInfo.queueCount; i++)
      {
        priorities.push_back(1.0f); // Push a new priority for each new queue
      }
      queueCreateInfo.pQueuePriorities = priorities.data();
      
      queueCreateInfos.push_back(queueCreateInfo);
    }
    
    
    
    VkPhysicalDeviceFeatures2 deviceFeatures = PhysicalDevice::GetSupportedDeviceFeatures();
    
    
    
    
    
    VkPhysicalDeviceShaderDrawParametersFeatures drawParametersFeatures{};
    drawParametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
    drawParametersFeatures.shaderDrawParameters = VK_TRUE;
    
    // Create the logical device
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    
    createInfo.pEnabledFeatures = &deviceFeatures.features;
    
    createInfo.pNext = &drawParametersFeatures;
    
    createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanDeviceManager::DEVICE_EXTENSIONS.size());
    createInfo.ppEnabledExtensionNames = VulkanDeviceManager::DEVICE_EXTENSIONS.data();
    
    // Required by older versions of vulkan which had distinctions between instance and device specific validation layers.
    // This is no longer the case so this is unneeded.
    // KEEP THIS HERE IN CASE OF COMPATIBILITY ISSUES!!!
    /*
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }*/
    
    CANDY_VULKAN_CHECK(vkCreateDevice(*physicalDevice, &createInfo, nullptr, &device));
    
    //std::unordered_map<uint32_t, uint32_t> queueCounts;
    vkGetDeviceQueue(device, queueFamilyIndices.graphicsFamily.value(), queueIndices[0], &graphicsQueue);
    vkGetDeviceQueue(device, queueFamilyIndices.presentFamily.value(), queueIndices[1], &presentQueue);
    vkGetDeviceQueue(device, queueFamilyIndices.computeFamily.value(), queueIndices[2], &computeQueue);
    vkGetDeviceQueue(device, queueFamilyIndices.transferFamily.value(), queueIndices[3], &transferQueue);
    
    
    
    Vulkan::DeletionQueue().Push(device);
  }
  QueueFamilyIndices LogicalDevice::GetQueueFamilyIndices() const
  {
    return queueFamilyIndices;
  }
  void LogicalDevice::FindQueueFamilies(VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    
    
    std::vector<VkQueueFamilyProperties> queueFamilies = physicalDevice->GetQueueFamilyProperties();
    
    
    // Find at least one queue family that supports VK_QUEUE_GRAPHICS_BIT
    int i = 0;
    bool dedicatedCompute=false;
    bool dedicatedTransfer=false;
    for (const auto& queueFamily: queueFamilies)
    {
      int famFlagCount=0;
      if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
        famFlagCount++;
        queueFamilyIndices.graphicsFamily = i;
      }
      if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
      {
        famFlagCount++;
        if (! dedicatedCompute)
        {
          queueFamilyIndices.computeFamily = i;
        }
        
      }
      if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
      {
        famFlagCount++;
        if (! dedicatedTransfer)
        {
          queueFamilyIndices.transferFamily = i;
        }
      }
      if ((queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) && !(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !(queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT))
      {
        dedicatedCompute = true;
        queueFamilyIndices.computeFamily = i;
      }
      if ((queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) && !(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !(queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT))
      {
        dedicatedTransfer = true;
        queueFamilyIndices.transferFamily = i;
      }
      
      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(*physicalDevice, i, surface, &presentSupport);
      if (presentSupport)
      {
        queueFamilyIndices.presentFamily = i;
      }
      if (queueFamilyIndices.IsComplete())
      {
        break;
      }
      i++;
    }
    
    
    
   
  }
  
  
}