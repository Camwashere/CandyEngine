#pragma once
#include <CandyPch.hpp>
#include <vma/vk_mem_alloc.h>
#include <candy/utils/Version.hpp>

struct GLFWwindow;
namespace Candy::Graphics
{
 
  class GraphicsContext;
  class DeletionQueue;
  class PhysicalDevice;
  class LogicalDevice;
  class DescriptorAllocator;
  class DescriptorLayoutCache;
  
  class Vulkan
  {
    static constexpr uint32_t MAX_CONTEXTS = 1;
    
    
    static void InitInstance(const std::string& appName, const Version& appVersion);
    static void InitDeviceManager(VkSurfaceKHR surface);

    
  public:
    static GraphicsContext* Init(GLFWwindow* mainWindow);
    static void Shutdown();
    static DeletionQueue& DeletionQueue();
    static VkInstance Instance();
    static VmaAllocator Allocator();
    static PhysicalDevice& PhysicalDevice();
    static LogicalDevice& LogicalDevice();
    static bool HasDeviceManager();
    static const std::filesystem::path& GetVulkanFeaturesPath();
    static DescriptorAllocator& GetDescriptorAllocator();
    static DescriptorLayoutCache& GetDescriptorLayoutCache();
    
    static GraphicsContext& GetCurrentContext();
    
    static float GetContextSizeRatio();
    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkSurfaceFormatKHR GetSurfaceFormat(VkSurfaceKHR surface);
    static int GetFramesInFlight();
    
    
  private:
    friend class GraphicsContext;
    
  
  
  };
}