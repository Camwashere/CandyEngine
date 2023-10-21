#include <candy/graphics/vulkan/RenderChainScheduler.hpp>
#include "CandyPch.hpp"
namespace Candy::Graphics
{
  RenderChainScheduler::RenderChainScheduler()
  {
  
  }
  RenderChain& RenderChainScheduler::operator[](uint32_t chainIndex)
  {
    CANDY_CORE_ASSERT(chainIndex < renderChains.size(), "RenderChainScheduler::operator[]: chainIndex out of bounds");
    return renderChains[chainIndex];
  }
  const RenderChain& RenderChainScheduler::operator[](uint32_t chainIndex)const
  {
    CANDY_CORE_ASSERT(chainIndex < renderChains.size(), "RenderChainScheduler::operator[]: chainIndex out of bounds");
    return renderChains[chainIndex];
  }
  RenderPass& RenderChainScheduler::operator[](uint32_t chainIndex, uint32_t passIndex)
  {
    CANDY_CORE_ASSERT(chainIndex < renderChains.size(), "RenderChainScheduler::operator[]: chainIndex out of bounds");
    CANDY_CORE_ASSERT(passIndex < renderChains[chainIndex].GetTotalPassCount());
    return renderChains[chainIndex][passIndex];
  }
  const RenderPass& RenderChainScheduler::operator[](uint32_t chainIndex, uint32_t passIndex)const
  {
    CANDY_CORE_ASSERT(chainIndex < renderChains.size(), "RenderChainScheduler::operator[]: chainIndex out of bounds");
    CANDY_CORE_ASSERT(passIndex < renderChains[chainIndex].GetTotalPassCount());
    return renderChains[chainIndex][passIndex];
  }
  
  
  uint32_t RenderChainScheduler::AddChain(const std::string& name)
  {
    auto it = chainNameMap.find(name);
    CANDY_CORE_ASSERT_MSG(it == chainNameMap.end(), "Cannot add render chain with name {0}, because it already exists", name);
    renderChains.emplace_back(name);
    uint32_t index = renderChains.size()-1;
    chainNameMap[name] = index;
    return index;
  }
  RenderChainPassKey RenderChainScheduler::AddPass(const std::string& chainName, const std::string& passName, const RenderPassConfig& config, bool startActive)
  {
    auto it = chainNameMap.find(chainName);
    if (it == chainNameMap.end())
    {
      uint32_t index = AddChain(chainName);
      uint32_t pIndex = renderChains[index].AddPass(passName, config, startActive);
      return {index, pIndex};
    }
    RenderChainPassKey key{};
    key.chainIndex = it->second;
    key.passIndex = renderChains[it->second].AddPass(passName, config, startActive);
    return key;
  }
  
  void RenderChainScheduler::SetSwapChainTarget(FrameBuffer& swapChainFrameBuffer)
  {
    swapChainTarget.frameBuffer = swapChainFrameBuffer;
  }
  void RenderChainScheduler::Begin(const Math::Vector2u& renderAreaSize)
  {
    //CANDY_CORE_ASSERT(frameBuffer != nullptr, "Cannot begin render chain scheduler with nullptr framebuffer!");
    //swapChainTarget.frameBuffer = currentSwapChainFrameBuffer;
    
    for (auto& chain : renderChains)
    {
      chain.renderAreaSize = renderAreaSize;
      chain.Refresh();
    }
    needsReset=false;
    chainIndex=0;
    for (RenderPass& pass : renderChains.back().renderPasses)
    {
      pass.SetRenderTarget(swapChainTarget);
    }
    //renderChains.back().GetLastActivePass().SetRenderTarget(swapChainTarget);
    renderChains[chainIndex].Begin();
    
  }
  void RenderChainScheduler::End()
  {
    
    if (renderChains[chainIndex].IsRunning())
    {
      //renderChains[chainIndex].GetLastActivePass().SetRenderTarget(swapChainTarget);
      renderChains[chainIndex].End();
    }
    needsReset=true;
    //currentFrameBuffer=nullptr;
  }
  bool RenderChainScheduler::Next()
  {
    if (needsReset)
    {
      return false;
    }
    if (NextPass())
    {
      return true;
    }
    else
    {
      return NextChain();
    }
    
  }
  bool RenderChainScheduler::NextChain()
  {
    if (needsReset)
    {
      return false;
    }
    uint32_t previousChainIndex = chainIndex;
    chainIndex++;
    if (chainIndex < renderChains.size())
    {
      if (renderChains[previousChainIndex].IsRunning())
      {
        renderChains[previousChainIndex].End();
      }
      renderChains[chainIndex].Begin();
      return true;
    }
    else if (chainIndex == renderChains.size())
    {
      CANDY_CORE_ERROR("Called next chain when there are no more chains left");
      //End();
    }
    
    return false;
    
  }
  bool RenderChainScheduler::NextPass()
  {
    if (needsReset)
    {
      return false;
    }
    return renderChains[chainIndex].NextPass();
   
    //currentKey.passIndex = renderChains[chainIndex].GetCurrentPassIndex();
    
    
  }
  bool RenderChainScheduler::NeedsReset()const
  {
    return needsReset;
  }
  RenderChainPassKey RenderChainScheduler::GetCurrentKey()const
  {
    return {chainIndex, renderChains[chainIndex].GetCurrentPassIndex()};
  }
  RenderPass& RenderChainScheduler::GetCurrentRenderPass()
  {
    CANDY_CORE_ASSERT_MSG(chainIndex < renderChains.size(), "RenderChainScheduler::GetCurrentRenderPass: chainIndex out of bounds with value {0}", chainIndex);
    return renderChains[chainIndex].GetCurrentPass();
  }
  uint32_t RenderChainScheduler::GetCurrentChainIndex()const
  {
    return chainIndex;
  }
  uint32_t RenderChainScheduler::GetCurrentPassIndex()const
  {
    return renderChains[chainIndex].GetCurrentPassIndex();
  }
}