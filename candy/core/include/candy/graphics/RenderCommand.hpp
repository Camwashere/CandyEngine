#pragma once
#include <vulkan/vulkan.h>
#include <functional>
namespace Candy::Graphics
{
  struct UploadContext
  {
    VkFence uploadFence;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
  };
  
  class RenderCommand
  {
    private:
    static UploadContext uploadContext;
  private:
    static VkCommandBufferBeginInfo CommandBufferBeginInfo(VkCommandBufferUsageFlags flags=0);
    static VkSubmitInfo SubmitInfo(VkCommandBuffer* cmd);
    static void InitCommands();
    static void InitSyncStructures();
  public:
    static void Init();
    static void ImmediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function);
    static void Shutdown();
    
  };
}