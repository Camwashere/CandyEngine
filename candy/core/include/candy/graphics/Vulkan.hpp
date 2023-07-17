#pragma once
#include <CandyPch.hpp>
#include <vma/vk_mem_alloc.h>
#include "vulkan/device/VulkanDeviceManager.hpp"
struct GLFWwindow;

namespace Candy::Graphics
{
 
  class GraphicsContext;
  class VulkanInstance;
  
  class Vulkan
  {
    static constexpr uint32_t MAX_CONTEXTS = 1;
  private:
    static Vulkan* vulkan;
  private:
    UniquePtr<VulkanInstance> instance;
    VulkanDeviceManager* deviceManager;
    VmaAllocator allocator;
    
    
  private:
    void CreateAllocator();
    static void InitDeviceManager(VkSurfaceKHR surface);
    
  public:
    Vulkan();
    
  public:
    static void Init();
    static void Shutdown();
    
    static VkInstance Instance();
    static VmaAllocator Allocator();
    static PhysicalDevice& PhysicalDevice();
    static LogicalDevice& LogicalDevice();
    static bool HasDeviceManager();
    
  private:
    friend class GraphicsContext;
    
  
  
  };
}