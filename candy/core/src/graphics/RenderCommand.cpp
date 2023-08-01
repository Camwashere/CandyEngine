#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  void RenderCommand::InitSyncStructures()
  {
    VkFenceCreateInfo uploadFenceCreateInfo{};
    uploadFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    
    
    CANDY_CORE_ASSERT(vkCreateFence(Vulkan::LogicalDevice(), &uploadFenceCreateInfo, nullptr, &uploadContext.uploadFence)==VK_SUCCESS);
    Vulkan::DeletionQueue().Push(uploadContext.uploadFence);
    //Vulkan::PushDeleter([=](){vkDestroyFence(Vulkan::LogicalDevice(), uploadContext.uploadFence, nullptr);});
  }
  UploadContext RenderCommand::uploadContext;
  VkCommandBufferBeginInfo RenderCommand::CommandBufferBeginInfo(VkCommandBufferUsageFlags flags)
  {
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.pNext = nullptr;
    
    info.pInheritanceInfo = nullptr;
    info.flags = flags;
    return info;
  }
  VkSubmitInfo RenderCommand::SubmitInfo(VkCommandBuffer* cmd)
  {
    VkSubmitInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;
    
    info.waitSemaphoreCount = 0;
    info.pWaitSemaphores = nullptr;
    info.pWaitDstStageMask = nullptr;
    info.commandBufferCount = 1;
    info.pCommandBuffers = cmd;
    info.signalSemaphoreCount = 0;
    info.pSignalSemaphores = nullptr;
    
    return info;
  }
  
  void RenderCommand::InitCommands()
  {
    QueueFamilyIndices queueFamilyIndices = Vulkan::PhysicalDevice().FindQueueFamilies(Vulkan::GetCurrentContext().GetSurface());
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    //create pool for upload context
    CANDY_CORE_ASSERT(vkCreateCommandPool(Vulkan::LogicalDevice(), &poolInfo, nullptr, &uploadContext.commandPool)==VK_SUCCESS);
    Vulkan::DeletionQueue().Push<VkCommandPool>(uploadContext.commandPool);
    //Vulkan::PushDeleter([=](){vkDestroyCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, nullptr);});
    
    
    //allocate the default command buffer that we will use for the instant commands
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = uploadContext.commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    //allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
    allocInfo.commandBufferCount=1;
    
    VkCommandBuffer cmd;
    CANDY_CORE_ASSERT(vkAllocateCommandBuffers(Vulkan::LogicalDevice(), &allocInfo, &uploadContext.commandBuffer)==VK_SUCCESS);
  }
  void RenderCommand::Init()
  {
    InitSyncStructures();
    InitCommands();
  }
  void RenderCommand::ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function)
  {
    VkCommandBuffer cmd = uploadContext.commandBuffer;
    
    //begin the command buffer recording. We will use this command buffer exactly once before resetting, so we tell vulkan that
    VkCommandBufferBeginInfo cmdBeginInfo = CommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    
    CANDY_CORE_ASSERT(vkBeginCommandBuffer(cmd, &cmdBeginInfo)==VK_SUCCESS);
    
    //execute the function
    function(cmd);
    
    CANDY_CORE_ASSERT(vkEndCommandBuffer(cmd)==VK_SUCCESS);
    
    VkSubmitInfo submit = SubmitInfo(&cmd);
    
    
    //submit command buffer to the queue and execute it.
    // uploadFence will now block until the graphic commands finish execution
    CANDY_CORE_ASSERT(vkQueueSubmit(Vulkan::LogicalDevice().graphicsQueue, 1, &submit, uploadContext.uploadFence)==VK_SUCCESS);
    
    vkWaitForFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence, true, 9999999999);
    vkResetFences(Vulkan::LogicalDevice(), 1, &uploadContext.uploadFence);
    
    // reset the command buffers inside the command pool
    vkResetCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, 0);
  }
  
  /*void RenderCommand::Shutdown()
  {
    vkDestroyCommandPool(Vulkan::LogicalDevice(), uploadContext.commandPool, nullptr);
    vkDestroyFence(Vulkan::LogicalDevice(), uploadContext.uploadFence, nullptr);
    
  }*/
}