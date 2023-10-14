#pragma once
#include <vector>
#include <candy/graphics/vulkan/RenderPass.hpp>
#include <unordered_map>
namespace Candy::Graphics
{
  class RenderChain
  {
  private:
    std::string chainName;
    std::vector<RenderPass> renderPasses;
    std::unordered_map<std::string, uint32_t> passNameMap;
    std::vector<bool> activePasses;
    std::vector<uint32_t> activePassIndices;
    
    uint32_t activePassIndex=0;
    uint32_t currentPassIndex=0;
    bool needsReset=true;
    bool needsActivePassUpdate=false;
    bool running=false;
    
  private:
    void UpdateActivePasses();
    bool IncrementActivePassIndex();
    void ResetPassIndex();
    
  public:
    explicit RenderChain(std::string name);
    RenderPass& operator[](uint32_t index);
    const RenderPass& operator[](uint32_t index)const;
    
  public:
    bool NeedsReset()const;
    std::string GetName()const;
    void Begin();
    void End();
    bool IsRunning()const;
    uint32_t GetPassIndex(const std::string& name)const;
    bool NextPass();
    void SetActivePass(const std::string& name, bool active=true);
    void SetActivePass(uint32_t index, bool active=true);
    void ActivatePass(uint32_t index);
    void DisablePass(uint32_t index);
    RenderPass& GetCurrentPass();
    uint32_t GetCurrentPassIndex()const;
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