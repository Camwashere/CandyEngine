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
  
  void Vulkan::CreateAllocators()
  {
    VmaAllocatorCreateInfo allocatorCreateInfo = {};
    allocatorCreateInfo.physicalDevice = deviceManager->physicalDevice;
    allocatorCreateInfo.device = deviceManager->logicalDevice;
    allocatorCreateInfo.instance = instance->instance;
    
    CANDY_CORE_ASSERT(vmaCreateAllocator(&allocatorCreateInfo, &allocator) == VK_SUCCESS, "FAILED TO CREATE ALLOCATOR");
    
    descriptorAllocator = CreateUniquePtr<DescriptorAllocator>(deviceManager->logicalDevice);
  }
  void Vulkan::InitDeviceManager(VkSurfaceKHR surface)
  {
    vulkan->deviceManager = new VulkanDeviceManager(surface);
    vulkan->CreateAllocators();
  }
  void Vulkan::Init()
  {
    
    vulkan = new Vulkan();
    Renderer::Init();
    
  }
 /* DeletionQueue& Vulkan::GetDeletionQueue()
  {
    return vulkan->deletionQueue;
  }*/
 /*template<typename T>
 void Vulkan::Push(T object)
 {
   vulkan->deletionQueue.Push<T>(object);
 }*/
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
    return GetCurrentContext().GetCurrentFrame().commandBuffer;
  }
  float Vulkan::GetContextSizeRatio()
  {
    return (float)GetCurrentContext().swapChain->extent.width / (float)GetCurrentContext().swapChain->extent.height;
  }

  
  void Vulkan::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
  {
    CommandBuffer* cmd = &Vulkan::GetCurrentContext().GetCurrentFrame().commandBuffer;
    
    VkCommandBuffer commandBuffer = cmd->BeginSingleTimeCommands();
    
    VkBufferCopy copyRegion{};
    copyRegion.srcOffset = 0; // Optional
    copyRegion.dstOffset = 0; // Optional
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    
    cmd->EndSingleTimeCommands(commandBuffer);
  }
  void Vulkan::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
  {
    GetCurrentCommandBuffer().TransitionImageLayout(image, format, oldLayout, newLayout);
  
  }
  void Vulkan::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
  {
    GetCurrentCommandBuffer().CopyBufferToImage(buffer, image, width, height);
  
  }
  /*void Vulkan::PushDeleter(std::function<void()>&& function)
  {
    vulkan->deletionQueue.PushFunction(std::move(function));
  }*/
  void Vulkan::Shutdown()
  {
    vkDeviceWaitIdle(LogicalDevice());
    //vulkan->contexts[0]->Terminate();
    vulkan->deletionQueue.Flush();
    vulkan->descriptorAllocator->Flip();
    vulkan->descriptorAllocator.reset();
    vulkan->descriptorLayoutCache.Destroy();
    vmaDestroyAllocator(vulkan->allocator);
    vulkan->deviceManager->Destroy();
   
  }
}