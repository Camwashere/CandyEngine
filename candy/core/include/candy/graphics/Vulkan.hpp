#pragma once
#include <CandyPch.hpp>
#include <vma/vk_mem_alloc.h>
#include "vulkan/device/VulkanDeviceManager.hpp"
#include "vulkan/descriptor/DescriptorAllocator.hpp"
#include "vulkan/descriptor/DescriptorLayoutCache.hpp"
#include "GraphicsContext.hpp"
#include "Renderer.hpp"
#include "vulkan/DeletionQueue.hpp"
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
    UniquePtr<DescriptorAllocator> descriptorAllocator;
    DescriptorLayoutCache descriptorLayoutCache;
    std::vector<GraphicsContext*> contexts;
    GraphicsContext* currentContext;
    DeletionQueue deletionQueue;
    
  private:
    void CreateAllocators();
    static void InitDeviceManager(VkSurfaceKHR surface);
    
  public:
    Vulkan();
    
  public:
    static void Init();
    static void Shutdown();
    //static void PushDeleter(std::function<void()>&& function);
    /*template<typename T>
    static void Push(T object)
    {
      CANDY_CORE_ASSERT(false, "Unknown vulkan object type");
      vulkan->deletionQueue.Push<T>(object);
    }*/
    static DeletionQueue& DeletionQueue();
    static VkInstance Instance();
    static VmaAllocator Allocator();
    static PhysicalDevice& PhysicalDevice();
    static LogicalDevice& LogicalDevice();
    static bool HasDeviceManager();
    static DescriptorAllocator& GetDescriptorAllocator();
    static DescriptorLayoutCache& GetDescriptorLayoutCache();
    static void RegisterContext(GraphicsContext* context);
    static GraphicsContext& GetCurrentContext();
    static CommandBuffer& GetCurrentCommandBuffer();
    static float GetContextSizeRatio();
    static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    static void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    static void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    
  private:
    friend class GraphicsContext;
    
  
  
  };
}