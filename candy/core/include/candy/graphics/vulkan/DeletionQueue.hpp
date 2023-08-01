#pragma once
#include <deque>
#include <functional>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/graphics/vulkan/ImageView.hpp>
#include <candy/graphics/GraphicsContext.hpp>
namespace Candy::Graphics
{
  class DeletionQueue
  {
  private:
    //std::deque<std::function<void()>> queue;
    std::vector<VkSwapchainKHR> swapChains;
    std::vector<VkFramebuffer> frameBuffers;
    std::vector<Image*> images;
    std::vector<ImageView*> imageViews;
    std::vector<VkRenderPass> renderPasses;
    std::vector<VkPipelineLayout> pipelineLayouts;
    std::vector<VkPipeline> pipelines;
    std::vector<VkCommandPool> commandPools;
    std::vector<VkFence> fences;
    std::vector<VkSemaphore> semaphores;
    std::vector<VulkanBuffer*> buffers;
    
    
    
    
  public:
    //void PushFunction(std::function<void()>&& function);
    /*void PushSwapChain(VkSwapchainKHR swapChain);
    void PushImageView(ImageView* imageView);
    void PushRenderPass(VkRenderPass renderPass);
    void PushPipelineLayout(VkPipelineLayout pipelineLayout);
    void PushPipeline(VkPipeline pipeline);
    void PushCommandPool(VkCommandPool commandPool);
    void PushBuffer(VulkanBuffer* buffer);
    void PushFence(VkFence fence);
    void PushSemaphore()*/
    template<typename T>
    void Push(T vulkanObject);
    
  
  void Flush();
    
  };
  template<>
  void DeletionQueue::Push<VkSwapchainKHR>(VkSwapchainKHR vulkanObject);
  template<>
  void DeletionQueue::Push<VkFramebuffer>(VkFramebuffer vulkanObject);
  template<>
  void DeletionQueue::Push<Image*>(Image* vulkanObject);
  template<>
  void DeletionQueue::Push<ImageView*>(ImageView* vulkanObject);
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
  void DeletionQueue::Push<VertexBuffer*>(VertexBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<IndexBuffer*>(IndexBuffer* vulkanObject);
  template<>
  void DeletionQueue::Push<VkFence>(VkFence vulkanObject);
  template<>
  void DeletionQueue::Push<VkSemaphore>(VkSemaphore vulkanObject);
  /*template<>
  void DeletionQueue::Push<VkSwapchainKHR>(VkSwapchainKHR vulkanObject)
  {
    swapChains.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkFramebuffer>(VkFramebuffer vulkanObject)
  {
    frameBuffers.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<Image*>(Image* vulkanObject)
  {
    images.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<ImageView*>(ImageView* vulkanObject)
  {
    imageViews.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkRenderPass>(VkRenderPass vulkanObject)
  {
    renderPasses.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkPipelineLayout>(VkPipelineLayout vulkanObject)
  {
    pipelineLayouts.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkPipeline>(VkPipeline vulkanObject)
  {
    pipelines.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkCommandPool>(VkCommandPool vulkanObject)
  {
    commandPools.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VulkanBuffer*>(VulkanBuffer* vulkanObject)
  {
    buffers.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkFence>(VkFence vulkanObject)
  {
    fences.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkSemaphore>(VkSemaphore vulkanObject)
  {
    semaphores.push_back(vulkanObject);
  }*/
  
  
}

