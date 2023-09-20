#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <ranges>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  /*void DeletionQueue::PushFunction(std::function<void()>&& function)
  {
    queue.push_back(std::move(function));
  }*/
  
  /*void DeletionQueue::PushSwapChain(VkSwapchainKHR swapChain)
  {
    swapChains.push_back(swapChain);
  }
  void DeletionQueue::PushImageView(ImageView* imageView)
  {
    imageViews.push_back(imageView);
  }
  void DeletionQueue::PushRenderPass(VkRenderPass renderPass)
  {
    renderPasses.push_back(renderPass);
  }
  void DeletionQueue::PushPipelineLayout(VkPipelineLayout pipelineLayout)
  {
    pipelineLayouts.push_back(pipelineLayout);
  }
  void DeletionQueue::PushPipeline(VkPipeline pipeline)
  {
    pipelines.push_back(pipeline);
  }
  void DeletionQueue::PushCommandPool(VkCommandPool commandPool)
  {
    commandPools.push_back(commandPool);
  }
  void DeletionQueue::PushBuffer(VkBuffer buffer)
  {
    buffers.push_back(buffer);
  }*/
  
  void DeletionQueue::Flush()
  {
    CANDY_PROFILE_FUNCTION();
    //Clean();
    for (auto fence : fences)
    {
      vkDestroyFence(Vulkan::LogicalDevice(), fence, nullptr);
    }
    fences.clear();
    
    for (auto semaphore : semaphores)
    {
      vkDestroySemaphore(Vulkan::LogicalDevice(), semaphore, nullptr);
    }
    semaphores.clear();

// 3. VulkanBuffer objects - These may include VkBuffer and VkDeviceMemory which make up the buffer.
    
    for(auto buffer : buffers) {
      vmaDestroyBuffer(Vulkan::Allocator(), *buffer, buffer->GetAllocation());
    }
    buffers.clear();

// 4. Command Pools
    
    for(auto& commandPool : commandPools) {
      vkDestroyCommandPool(Vulkan::LogicalDevice(), commandPool, nullptr);
    }
    commandPools.clear();

// 5. Pipelines
    
    for(auto& pipeline : pipelines) {
      vkDestroyPipeline(Vulkan::LogicalDevice(), pipeline, nullptr);
    }
    pipelines.clear();

// 6. Pipeline Layouts
    
    for(auto& pipelineLayout : pipelineLayouts) {
      vkDestroyPipelineLayout(Vulkan::LogicalDevice(), pipelineLayout, nullptr);
    }
    pipelineLayouts.clear();

// 7. Render Passes
    
    for(auto& renderPass : renderPasses) {
      vkDestroyRenderPass(Vulkan::LogicalDevice(), renderPass, nullptr);
    }
    renderPasses.clear();

// 8. ImageView objects
    
    for(auto imageView : imageViews) {
      vkDestroyImageView(Vulkan::LogicalDevice(), *imageView, nullptr);
      vkDestroySampler(Vulkan::LogicalDevice(), imageView->GetSampler(), nullptr);
    }
    imageViews.clear();

// 9. Image objects
    
    for(auto image : images) {
      vmaDestroyImage(Vulkan::Allocator(), *image, image->GetAllocation());
    }
    images.clear();

// 10. Frame Buffers
    
    for(auto& framebuffer : frameBuffers) {
      vkDestroyFramebuffer(Vulkan::LogicalDevice(), *framebuffer, nullptr);
    }
    frameBuffers.clear();

// 11. Swap Chains
    
    for(auto& swapChain : swapChains) {
      vkDestroySwapchainKHR(Vulkan::LogicalDevice(), swapChain, nullptr);
    }
    swapChains.clear();
  }
  
  template<typename T>
  void DeletionQueue::Delete(T vulkanObject)
  {
    CANDY_CORE_ASSERT(false, "DeletionQueue::Delete<T> is not implemented for this type!");
  }
  template<>
  void DeletionQueue::Delete<VkSwapchainKHR>(VkSwapchainKHR vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    vkDestroySwapchainKHR(Vulkan::LogicalDevice(), vulkanObject, nullptr);
    swapChains.erase(vulkanObject);
  }
  
  template<>
  void DeletionQueue::Delete<FrameBuffer*>(FrameBuffer* vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    vkDestroyFramebuffer(Vulkan::LogicalDevice(), *vulkanObject, nullptr);
    frameBuffers.erase(vulkanObject);
  }
  template<>
  void DeletionQueue::Delete<StorageBuffer*>(StorageBuffer* vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    VulkanBuffer::DestroyBuffer(vulkanObject);
    buffers.erase(vulkanObject);
  }
  template<>
  void DeletionQueue::Delete<PixelBuffer*>(PixelBuffer* vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    VulkanBuffer::DestroyBuffer(vulkanObject);
    buffers.erase(vulkanObject);
  }
  template<>
  void DeletionQueue::Delete<Image*>(Image* vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    vmaDestroyImage(Vulkan::Allocator(), *vulkanObject, vulkanObject->GetAllocation());
    images.erase(vulkanObject);
    
  }
  template<>
  void DeletionQueue::Delete<ImageView*>(ImageView* vulkanObject)
  {
    CANDY_PROFILE_FUNCTION();
    vkDestroyImageView(Vulkan::LogicalDevice(), *vulkanObject, nullptr);
    vkDestroySampler(Vulkan::LogicalDevice(), vulkanObject->GetSampler(), nullptr);
    imageViews.erase(vulkanObject);
  }
  
  template<typename T>
  void DeletionQueue::Push(T vulkanObject)
  {
    CANDY_CORE_ASSERT(false, "DeletionQueue::Push<T> is not implemented for this type!");
  }
  template<>
  void DeletionQueue::Push<VkSwapchainKHR>(VkSwapchainKHR vulkanObject)
  {
    swapChains.insert(vulkanObject);
  }
  
  template<>
  void DeletionQueue::Push<Image*>(Image* vulkanObject)
  {
    images.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<ImageView*>(ImageView* vulkanObject)
  {
    imageViews.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkRenderPass>(VkRenderPass vulkanObject)
  {
    renderPasses.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkPipelineLayout>(VkPipelineLayout vulkanObject)
  {
    pipelineLayouts.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkPipeline>(VkPipeline vulkanObject)
  {
    pipelines.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkCommandPool>(VkCommandPool vulkanObject)
  {
    commandPools.insert(vulkanObject);
    //commandPools.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VulkanBuffer*>(VulkanBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  
  template<>
  void DeletionQueue::Push<UniformBuffer*>(UniformBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<StorageBuffer*>(StorageBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VertexBuffer*>(VertexBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<IndexBuffer*>(IndexBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<PixelBuffer*>(PixelBuffer* vulkanObject)
  {
    buffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<FrameBuffer*>(FrameBuffer* vulkanObject)
  {
    frameBuffers.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkFence>(VkFence vulkanObject)
  {
    fences.insert(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VkSemaphore>(VkSemaphore vulkanObject)
  {
    semaphores.insert(vulkanObject);
  }

}
