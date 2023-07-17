#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace Candy::Graphics
{
    
    class VulkanDebugManager
    {
    private:
        
        VkDebugUtilsMessengerEXT debugMessenger;
        
    public:
        VulkanDebugManager();
        
    public:
        void Init(VkInstance instance);
        void Terminate();
        
    public:
        static bool ValidationLayersEnabled();
        static bool ValidationLayersSupported();
        static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        static const std::vector<const char*>& GetValidationLayers();
        static uint32_t GetValidationLayerCount();
    };
}