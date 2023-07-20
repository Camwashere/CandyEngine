#include <candy/graphics/vulkan/device/LogicalDevice.hpp>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <set>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
    LogicalDevice::LogicalDevice(const PhysicalDevice& physicalDevice, const QueueFamilyIndices& indices)
    {
       //QueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
        
        // Assign priority to queue to influence the scheduling of command buffer execution
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            // Describe number of queue we want for a single queue family.
            // Currently we only want one with graphics capabilities
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }
        
        
        
        
        // Specify the set of device features we will be using that we queried support for
        // in the IsDeviceSuitable function using vkGetPhysicalDeviceFeatures
        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy=VK_TRUE;
        
        // Create the logical device
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        
        createInfo.pEnabledFeatures = &deviceFeatures;
        
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
        
        CANDY_CORE_ASSERT(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) == VK_SUCCESS, "Failed to create vulkan logical device");
        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }
    
    
    
    
    
    
}