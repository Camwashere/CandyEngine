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
      vkDestroyFramebuffer(Vulkan::LogicalDevice(), framebuffer, nullptr);
    }
    frameBuffers.clear();

// 11. Swap Chains
    
    for(auto& swapChain : swapChains) {
      vkDestroySwapchainKHR(Vulkan::LogicalDevice(), swapChain, nullptr);
    }
    swapChains.clear();
  }
  /*void DeletionQueue::Flush()
  {
    
    for (auto & f : std::ranges::reverse_view(queue))
    {
      f();
    }
    queue.clear();
  }*/
  
  template<typename T>
  void DeletionQueue::Push(T vulkanObject)
  {
    CANDY_CORE_ASSERT(false, "DeletionQueue::Push<T> is not implemented for this type!");
  }
  template<>
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
  void DeletionQueue::Push<UniformBuffer*>(UniformBuffer* vulkanObject)
  {
    buffers.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<VertexBuffer*>(VertexBuffer* vulkanObject)
  {
    buffers.push_back(vulkanObject);
  }
  template<>
  void DeletionQueue::Push<IndexBuffer*>(IndexBuffer* vulkanObject)
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
  }

}
