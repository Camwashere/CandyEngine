#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include <string>


namespace Candy::Graphics
{
    /*struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> computeFamily;
        std::optional<uint32_t> transferFamily;
        
        [[nodiscard]] bool IsComplete() const
        {
          return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value();
        }
    };*/
    
    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    
    class PhysicalDevice
    {
    private:
        VkPhysicalDevice device=VK_NULL_HANDLE;
        VkPhysicalDeviceProperties properties{};
        VkPhysicalDeviceMemoryProperties memoryProperties{};
        size_t maxAllocationSize;
        std::string name;
        
        
    public:
        PhysicalDevice(VkSurfaceKHR surface);
        PhysicalDevice(const PhysicalDevice& other);
        
    public:
        operator VkPhysicalDevice(){return device;}
        operator VkPhysicalDevice()const{return device;}
        
    public:
        [[nodiscard]] bool IsValid()const;
        [[nodiscard]] const char* GetName()const;
        [[nodiscard]] uint32_t GetDriverVersion()const;
        [[nodiscard]] uint32_t GetApiVersion()const;
        [[nodiscard]] uint32_t GetVendorID()const;
        [[nodiscard]] uint32_t GetDeviceID()const;
        [[nodiscard]] size_t GetMinUniformBufferOffsetAlignment()const;
        [[nodiscard]] uint32_t GetMaxPushConstantSize()const;
        [[nodiscard]] uint32_t GetMaxDynamicUniformBufferCount()const;
        [[nodiscard]] uint32_t GetMaxUniformBufferSize()const;
        [[nodiscard]] size_t GetMaxAllocationSize()const;
        [[nodiscard]] VkPhysicalDeviceProperties GetProperties()const;
        [[nodiscard]] size_t PadUniformBufferSize(size_t originalSize)const;
        
        
    public:
        SwapChainSupportDetails QuerySwapChainSupport(VkSurfaceKHR surface);
        uint32_t GetQueueFamilyPropertyCount()const;
      std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties()const;
        //QueueFamilyIndices FindQueueFamilies(VkSurfaceKHR surface);
        bool IsDeviceSuitable(VkSurfaceKHR surface);
        bool CheckDeviceExtensionSupport();
        
    public:
      static VkPhysicalDeviceFeatures2 GetSupportedDeviceFeatures();
      static bool EnableDeviceFeature(const std::string& name);
      static bool EnableDeviceFeatures(const std::vector<std::string>& names);
      static bool CheckSupportedDeviceFeatures(const VkPhysicalDeviceFeatures2& features);
        static bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
        static long long int RateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface);
        static bool CheckExtensionSupport(VkPhysicalDevice device);
        static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
        //static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    };
}
