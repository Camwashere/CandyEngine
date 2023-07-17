#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
namespace Candy::Graphics
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        
        [[nodiscard]] bool IsComplete() const
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    
    class PhysicalDevice
    {
    private:
        VkPhysicalDevice device;
        
    public:
        PhysicalDevice();
        explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
        PhysicalDevice(const PhysicalDevice& other);
        
    public:
        operator VkPhysicalDevice(){return device;}
        operator VkPhysicalDevice()const{return device;}
        
    public:
        [[nodiscard]] bool IsValid()const;
        
        
        
    public:
        SwapChainSupportDetails QuerySwapChainSupport(VkSurfaceKHR surface);
        QueueFamilyIndices FindQueueFamilies(VkSurfaceKHR surface);
        bool IsDeviceSuitable(VkSurfaceKHR surface);
        bool CheckDeviceExtensionSupport();
        
    public:
        static bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
        static bool CheckExtensionSupport(VkPhysicalDevice device);
        static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    };
}
