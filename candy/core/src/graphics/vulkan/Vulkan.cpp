#include <candy/graphics/Vulkan.hpp>
#include "Candy/Graphics/GraphicsContext.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/vulkan/VulkanInstance.hpp>
namespace Candy::Graphics
{
  Vulkan* Vulkan::vulkan = nullptr;
  Vulkan::Vulkan()
  {
    deviceManager = nullptr;
    instance = CreateUniquePtr<VulkanInstance>();
    allocator = VK_NULL_HANDLE;
  }
  
  void Vulkan::CreateAllocator()
  {
    VmaAllocatorCreateInfo allocatorCreateInfo = {};
    allocatorCreateInfo.physicalDevice = deviceManager->physicalDevice;
    allocatorCreateInfo.device = deviceManager->logicalDevice;
    allocatorCreateInfo.instance = instance->instance;
    
    
    CANDY_CORE_ASSERT(vmaCreateAllocator(&allocatorCreateInfo, &allocator) == VK_SUCCESS, "FAILED TO CREATE ALLOCATOR");
  }
  void Vulkan::InitDeviceManager(VkSurfaceKHR surface)
  {
    vulkan->deviceManager = new VulkanDeviceManager(surface);
    vulkan->CreateAllocator();
  }
  void Vulkan::Init()
  {
    
    vulkan = new Vulkan();
    
  }
  
  VkInstance Vulkan::Instance()
  {
    
    return vulkan->instance->instance;
  }
  
  VmaAllocator Vulkan::Allocator()
  {
    return vulkan->allocator;
  }
  
  PhysicalDevice& Vulkan::PhysicalDevice()
  {
    return vulkan->deviceManager->physicalDevice;
  }
  LogicalDevice& Vulkan::LogicalDevice()
  {
    return vulkan->deviceManager->logicalDevice;
  }
  
  bool Vulkan::HasDeviceManager()
  {
    return vulkan->deviceManager != nullptr;
  }
  
  
  
  
  
  void Vulkan::Shutdown()
  {
    vmaDestroyAllocator(vulkan->allocator);
    vkDestroyDevice(LogicalDevice(), nullptr);
    vulkan->instance->Shutdown();
    //vulkanInstance->debugManager->Terminate();
    //vkDestroyInstance(instance, nullptr);
    //vkDestroyInstance(vulkanInstance->instance, nullptr);
  }
}