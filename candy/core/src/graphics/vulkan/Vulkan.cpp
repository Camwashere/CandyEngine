#include <candy/graphics/Vulkan.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/vulkan/VulkanInstance.hpp>
namespace Candy::Graphics
{
  Vulkan* Vulkan::vulkan = nullptr;
  Vulkan::Vulkan(const std::filesystem::path& featuresPath) : vulkanFeaturesPath(featuresPath)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(std::filesystem::exists(vulkanFeaturesPath), "Vulkan features file does not exist");
    deviceManager = nullptr;
    instance = CreateUniquePtr<VulkanInstance>();
    allocator = VK_NULL_HANDLE;
  }
  
  void Vulkan::CreateAllocators()
  {
    CANDY_PROFILE_FUNCTION();
    VmaAllocatorCreateInfo allocatorCreateInfo = {};
    
    allocatorCreateInfo.physicalDevice = deviceManager->physicalDevice;
    allocatorCreateInfo.device = deviceManager->logicalDevice;
    allocatorCreateInfo.instance = instance->instance;
    
    CANDY_VULKAN_CHECK(vmaCreateAllocator(&allocatorCreateInfo, &allocator));
    
    descriptorAllocator = CreateUniquePtr<DescriptorAllocator>();
  }
  void Vulkan::InitDeviceManager(VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    vulkan->deviceManager = new VulkanDeviceManager(surface);
    vulkan->CreateAllocators();
  }
  void Vulkan::Init()
  {
    CANDY_PROFILE_FUNCTION();
    vulkan = new Vulkan("config/vulkan/enabledVulkanFeatures.csv");
    
    Renderer::Init();
    
  }

 DeletionQueue& Vulkan::DeletionQueue()
 {
   
   return vulkan->deletionQueue;
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
  const std::filesystem::path& Vulkan::GetVulkanFeaturesPath()
  {
   return vulkan->vulkanFeaturesPath;
  }
  DescriptorAllocator& Vulkan::GetDescriptorAllocator()
  {
    return *vulkan->descriptorAllocator;
  }
  DescriptorLayoutCache& Vulkan::GetDescriptorLayoutCache()
  {
    return vulkan->descriptorLayoutCache;
  }
  VkSurfaceFormatKHR Vulkan::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
  {
    CANDY_PROFILE_FUNCTION();
    for (const auto& availableFormat : availableFormats)
    {
      if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        return availableFormat;
      }
    }
    return availableFormats[0];
  }
  void Vulkan::RegisterContext(GraphicsContext* context)
  {
    CANDY_PROFILE_FUNCTION();
    vulkan->contexts.push_back(context);
    vulkan->currentContext = context;
    Renderer::SetTarget(context);
    
    
  }
  

  GraphicsContext& Vulkan::GetCurrentContext()
  {
    CANDY_CORE_ASSERT(vulkan->currentContext, "FAILED TO GET CURRENT CONTEXT. THE CURRENT CONTEXT IS NULL");
    return *vulkan->currentContext;
  }

  CommandBuffer& Vulkan::GetCurrentCommandBuffer()
  {
    CANDY_PROFILE_FUNCTION();
    return GetCurrentContext().GetCurrentFrame().commandBuffer;
  }
  float Vulkan::GetContextSizeRatio()
  {
    return (float)GetCurrentContext().swapChain->extent.width / (float)GetCurrentContext().swapChain->extent.height;
  }

  void Vulkan::Shutdown()
  {
    CANDY_PROFILE_FUNCTION();
    vkDeviceWaitIdle(LogicalDevice());
    vulkan->deletionQueue.Flush();
    vulkan->descriptorAllocator->Reset();
    vulkan->descriptorAllocator.reset();
    vulkan->descriptorLayoutCache.Destroy();
    vmaDestroyAllocator(vulkan->allocator);
    vulkan->deviceManager->Destroy();
   
  }
}