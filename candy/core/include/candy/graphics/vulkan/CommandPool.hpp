#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <candy/base/Base.hpp>
namespace Candy::Graphics
{
  enum class CommandPoolType
  {
    None=0,
    SingleUse,
    OneTime=SingleUse,
    ShortLived,
    Transient=ShortLived,
    LongLived,
    Reset=LongLived,
  };

  class CommandPool
  {
  private:
    VkFence fence=nullptr;
    VkCommandPool pool=nullptr;
    std::vector<VkCommandBuffer> buffers;
    CommandPoolType type=CommandPoolType::None;
    
  public:
    CommandPool();
    explicit CommandPool(VkSurfaceKHR surface, CommandPoolType poolType=CommandPoolType::None, uint32_t bufferCount=0);
    
    void Init(VkSurfaceKHR surface, CommandPoolType poolType = CommandPoolType::None, uint32_t bufferCount = 0, bool startFenceSignaled=false);
    
    VkCommandBuffer GetCommandBuffer(uint32_t index=0);
    VkCommandBuffer BeginCommandBuffer(uint32_t index=0);
    
    VkResult ResetPool(bool releaseResources=false);
    VkResult ResetBuffer(uint32_t index=0, bool releaseResources=false);
    VkResult ResetBuffers(bool releaseResources=false);
    VkResult EndRecording();
    VkResult WaitFence(uint64_t timeout=UINT64_MAX);
    
  private:
    friend class RenderCommand;
    friend class GraphicsContext;
    
  };
}