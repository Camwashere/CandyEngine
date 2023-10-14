#pragma once
#include <vulkan/vulkan.h>
#include "device/VulkanDeviceManager.hpp"
#include <Candy/Math/Vector.hpp>
#include "../Color.hpp"
#include "../FrameBuffer.hpp"
#include <array>
#include <candy/graphics/vulkan/RenderPassConfig.hpp>
#include "RenderTarget.hpp"
namespace Candy::Graphics
{
  
  enum class RenderPassState
  {
    None=0,
    Running,
    Stopped,
  };
  
  
  
  
  class RenderPass
  {
  private:
    VkRenderPass renderPass = VK_NULL_HANDLE;
    std::string name;
    RenderPassState state = RenderPassState::None;
    std::vector<VkClearValue> clearValues{};
    RenderPassConfig config;
    RenderTarget* currentTarget=nullptr;
  
  public:
    RenderPass(std::string passName, RenderPassConfig configuration);
    
    operator VkRenderPass(); //NOLINT
    operator VkRenderPass() const; //NOLINT
  
  public:
    [[nodiscard]] const std::vector<VkClearValue>& GetClearValues()const;
    void SetClearValues(const std::vector<VkClearValue>& values);
    void SetRenderTarget(RenderTarget& target);
    RenderTarget* GetCurrentTarget();
    void Begin();
    void End();
    [[nodiscard]] bool IsRunning()const;
    [[nodiscard]] bool IsStopped()const;
    [[nodiscard]] RenderPassState GetCurrentState()const;
    [[nodiscard]] RenderPassConfig GetConfig()const;
    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] bool NeedsUniqueFrameBuffer() const;
    
    
  };
}