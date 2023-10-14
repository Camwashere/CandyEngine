#pragma once
#include "RenderChain.hpp"
namespace Candy::Graphics
{
  struct RenderChainPassKey
  {
    uint32_t chainIndex;
    uint32_t passIndex;
  };
  class RenderChainScheduler
  {
  private:
    std::vector<RenderChain> renderChains;
    std::unordered_map<std::string, uint32_t> chainNameMap;
    uint32_t chainIndex=0;
    
    bool needsReset=true;
    
  public:
    RenderChainScheduler();
    RenderChain& operator[](uint32_t chainIndex);
    const RenderChain& operator[](uint32_t chainIndex)const;
    RenderPass& operator[](uint32_t chainIndex, uint32_t passIndex);
    const RenderPass& operator[](uint32_t chainIndex, uint32_t passIndex)const;
    
  public:
    uint32_t AddChain(const std::string& name);
    RenderChainPassKey AddPass(const std::string& chainName, const std::string& passName, const RenderPassConfig& config, bool startActive=true);
    void Begin();
    void End();
    bool Next();
    bool NextChain();
    bool NextPass();
    bool NeedsReset()const;
    RenderChainPassKey GetCurrentKey()const;
    uint32_t GetCurrentChainIndex()const;
    uint32_t GetCurrentPassIndex()const;
    RenderPass& GetCurrentRenderPass();
    
  
  };
}