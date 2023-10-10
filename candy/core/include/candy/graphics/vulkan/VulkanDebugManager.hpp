#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include "VulkanPch.hpp"


namespace Candy::Graphics
{
    
    class VulkanDebugManager
    {
    private:
        VulkanDebugManager()=delete;
        
        
    public:
        //void Init(VkInstance instance);
        //void Terminate();
        
    public:
      static VkResult Init(VkInstance instance);
      static bool ValidationLayersEnabled();
      static bool ValidationLayersSupported();
      static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
      static const std::vector<const char*>& GetValidationLayers();
      static uint32_t GetValidationLayerCount();
      static std::vector<const char*> GetRequiredExtensions();
      static std::vector<std::string> GetAvailableExtensions();
      static void DisplayAvailableExtensions();
      static VkInstanceCreateInfo GetInstanceCreateInfo();
      static void Destroy();
    };
}