#pragma once
#include <deque>
#include <functional>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/VulkanImage.hpp>
#include <candy/graphics/vulkan/VulkanImageView.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/StorageBuffer.hpp>
#include <list>
#include <set>
#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/VertexBuffer.hpp>
#include <candy/graphics/IndexBuffer.hpp>
#include <candy/graphics/PixelBuffer.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorLayoutCache.hpp>
namespace Candy::Graphics
{
  class DeletionQueue
  {
  private:
    std::set<VkSwapchainKHR> swapChains;
    std::set<FrameBuffer*> frameBuffers;
    std::set<VulkanImage*> images;
    std::set<VulkanImageView*> imageViews;
    std::set<VkRenderPass> renderPasses;
    std::set<VkPipelineLayout> pipelineLayouts;
    std::set<VkPipeline> pipelines;
    std::set<VkCommandPool> commandPools;
    std::set<VkFence> fences;
    std::set<VkSemaphore> semaphores;
    std::set<VulkanBuffer*> buffers;
    std::set<VkSurfaceKHR> surfaces;
    std::set<DescriptorAllocator*> descriptorAllocators;
    std::set<DescriptorLayoutCache*> descriptorLayoutCaches;
    std::set<VkDevice> logicalDevices;
    
    
    
  public:
    template<typename T>
    void Push(T vulkanObject);
    template<typename T>
    void Delete(T vulkanObject);
    
    
    void Flush();
  };
  

  template<>
  void DeletionQueue::Push<VkDevice>(VkDevice vulkanObject);
  
  template<>
  void DeletionQueue::Push<VkSurfaceKHR>(VkSurfaceKHR vulkanObject);
  
  template<>
  void DeletionQueue::Push<DescriptorAllocator*>(DescriptorAllocator* vulkanObject);
  
  template<>
  void DeletionQueue::Push<DescriptorLayoutCache*>(DescriptorLayoutCache* vulkanObject);
  
  template<>
  void DeletionQueue::Push<VkSwapchainKHR>(VkSwapchainKHR vulkanObject);
  template<>
  void DeletionQueue::Push<VulkanImage*>(VulkanImage* vulkanObject);
  template<>
  void DeletionQueue::Push<VulkanImageView*>(VulkanImageView* vulkanObject);
  template<>
  void DeletionQueue::Push<VkRenderPass>(VkRenderPass vulkanObject);
  template<>
  void DeletionQueue::Push<VkPipelineLayout>(VkPipelineLayout vulkanObject);
  template<>
  void DeletionQueue::Push<VkPipeline>(VkPipeline vulkanObject);
  template<>
  void DeletionQueue::Push<VkCommandPool>(VkCommandPool vulkanObject);
  template<>
  void DeletionQueue::Push<VulkanBuffer*>(VulkanBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<UniformBuffer*>(UniformBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<StorageBuffer*>(StorageBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<VertexBuffer*>(VertexBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<IndexBuffer*>(IndexBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<PixelBuffer*>(PixelBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<FrameBuffer*>(FrameBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<VkFence>(VkFence vulkanObject);
  template<>
  void DeletionQueue::Push<VkSemaphore>(VkSemaphore vulkanObject);
  
  
  
  template<>
  void DeletionQueue::Delete<VkSwapchainKHR>(VkSwapchainKHR vulkanObject);
  template<>
  void DeletionQueue::Delete<VulkanImage*>(VulkanImage* vulkanObject);
  template<>
  void DeletionQueue::Delete<VulkanImageView*>(VulkanImageView* vulkanObject);
  template<>
  void DeletionQueue::Delete<FrameBuffer*>(FrameBuffer* vulkanObject);
  template<>
  void DeletionQueue::Delete<StorageBuffer*>(StorageBuffer* vulkanObject);
  template<>
  void DeletionQueue::Delete<PixelBuffer*>(PixelBuffer* vulkanObject);
  
  
}

