#pragma once
#include <deque>
#include <functional>
#include <vulkan/vulkan.h>
#include <CandyPch.hpp>
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/graphics/vulkan/ImageView.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <list>
#include <set>
namespace Candy::Graphics
{
  class DeletionQueue
  {
  private:
    //std::deque<std::function<void()>> queue;
    std::set<VkSwapchainKHR> swapChains;
    std::set<VkFramebuffer> frameBuffers;
    std::set<Image*> images;
    std::set<ImageView*> imageViews;
    std::set<VkRenderPass> renderPasses;
    std::set<VkPipelineLayout> pipelineLayouts;
    std::set<VkPipeline> pipelines;
    std::set<VkCommandPool> commandPools;
    std::set<VkFence> fences;
    std::set<VkSemaphore> semaphores;
    std::set<VulkanBuffer*> buffers;
    
    
    
    
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
    
    template<typename T>
    void Delete(T vulkanObject);
    
    //void RemoveFrameBuffer(VkFramebuffer frameBuffer);
    
    /*void CleanFrameBuffers();
    void CleanImages();
    void CleanImageViews();
    void Clean();*/
  
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
  
  
  template<>
  void DeletionQueue::Delete<VkSwapchainKHR>(VkSwapchainKHR vulkanObject);
  template<>
  void DeletionQueue::Delete<VkFramebuffer>(VkFramebuffer vulkanObject);
  template<>
  void DeletionQueue::Delete<Image*>(Image* vulkanObject);
  template<>
  void DeletionQueue::Delete<ImageView*>(ImageView* vulkanObject);
  
  
}

