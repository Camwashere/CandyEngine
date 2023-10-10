#pragma once
#include <vector>
#include <candy/graphics/vulkan/RenderPass.hpp>
namespace Candy::Graphics
{
  class RenderPassScheduler
  {
  private:
    
    std::vector<RenderPass> renderPasses;
    std::vector<bool> activePasses;
    std::vector<uint32_t> activePassIndices;
    
    uint32_t activePassIndex=0;
    uint32_t currentPassIndex=0;
    bool needsActivePassUpdate=false;
    bool running=false;
    
  private:
    void UpdateActivePasses();
    bool IncrementActivePassIndex();
    void ResetPassIndex();
    
  public:
    RenderPass& operator[](uint32_t index);
    const RenderPass& operator[](uint32_t index)const;
    
  public:
    bool Begin();
    bool End();
    bool NextPass();
    void SetActivePass(uint32_t index, bool active=true);
    void ActivatePass(uint32_t index);
    void DisablePass(uint32_t index);
    RenderPass& GetCurrentPass();
    RenderPass& GetPassAt(uint32_t index);
    [[nodiscard]] const RenderPass& GetCurrentPass()const;
    [[nodiscard]] const RenderPass& GetPassAt(uint32_t index)const;
    [[nodiscard]] std::string GetPassName(uint32_t index)const;
    [[nodiscard]] size_t GetTotalPassCount()const;
    [[nodiscard]] size_t GetActivePassCount()const;
    [[nodiscard]] bool IsPassActive(uint32_t index)const;
    uint32_t AddPass(const std::string& name, const RenderPassConfig& config, bool startActive=true);
    
    
  };
}