#include <candy/graphics/vulkan/RenderChain.hpp>
#include "CandyPch.hpp"
#include "candy/graphics/RenderCommand.hpp"
#include <candy/graphics/vulkan/RenderPassConfig.hpp>
#include <utility>
namespace Candy::Graphics
{
  
  
  RenderChain::RenderChain(std::string name) : chainName(std::move(name))
  {
  
  }
  std::string RenderChain::GetName()const
  {
    return chainName;
  }
  void RenderChain::Begin()
  {
    
    running=true;
    BeginCurrentPass();
  }
  
  void RenderChain::Refresh()
  {
    if (needsActivePassUpdate)
    {
      UpdateActivePasses();
    }
    ResetPassIndex();
    CANDY_CORE_ASSERT(! activePassIndices.empty());
  }
  
  void RenderChain::End()
  {
    CANDY_CORE_ASSERT_MSG(activePassIndex == activePassIndices.size()-1, "RenderChain::End: activePassIndex != activePassIndices.size()-1, current active index: {0}", activePassIndex);
    EndCurrentPass();
    running = false;
  }
  bool RenderChain::IsRunning()const
  {
    return running;
  }
  void RenderChain::UpdateActivePasses()
  {
    activePassIndices.clear();
    for (uint32_t i = 0; i < renderPasses.size(); i++)
    {
      if (activePasses[i])
      {
        activePassIndices.push_back(i);
      }
    }
  }
  void RenderChain::ResetPassIndex()
  {
    needsReset=false;
    activePassIndex=0;
    currentPassIndex=activePassIndices[activePassIndex];
  }
  
  void RenderChain::BeginCurrentPass()
  {
    CANDY_CORE_ASSERT(running, "RenderChain::BeginCurrentPass: RenderChain is not running");
    RenderPass& currentPass = renderPasses[currentPassIndex];
    currentPass.Begin();
    
    CANDY_CORE_ASSERT(currentPass.currentTarget != nullptr, "RenderPass::Begin: currentTarget is nullptr");
    
    VkRenderPassBeginInfo beginPassInfo{};
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = currentPass;
    beginPassInfo.framebuffer = currentPass.currentTarget->frameBuffer;
    beginPassInfo.renderArea.offset.x = renderAreaOffset.x;
    beginPassInfo.renderArea.offset.y = renderAreaOffset.y;
    beginPassInfo.renderArea.extent.width = renderAreaSize.width;
    beginPassInfo.renderArea.extent.height = renderAreaSize.height;
    
    beginPassInfo.clearValueCount = currentPass.clearValues.size();
    beginPassInfo.pClearValues = currentPass.clearValues.data();
    
    RenderCommand::BeginRenderPass(&beginPassInfo);
    
    Math::Vector2u position = {0, 0};
    RenderCommand::SetViewport(position, renderAreaSize);
  }
  void RenderChain::EndCurrentPass()
  {
    renderPasses[currentPassIndex].End();
    RenderCommand::EndRenderPass();
  }
  bool RenderChain::IncrementActivePassIndex()
  {
    if (needsReset)
    {
      return false;
    }
    if (activePassIndex+1 >= activePassIndices.size())
    {
      needsReset=true;
      return false;
    }
    else
    {
      activePassIndex++;
      currentPassIndex = activePassIndices[activePassIndex];
      return true;
    }
  }
  
  uint32_t RenderChain::GetCurrentPassIndex()const
  {
    return currentPassIndex;
  }
  uint32_t RenderChain::GetPassIndex(const std::string& name)const
  {
    auto it = passNameMap.find(name);
    CANDY_CORE_ASSERT(it != passNameMap.end());
    return it->second;
  }
  void RenderChain::SetActivePass(const std::string& name, bool active)
  {
    auto it = passNameMap.find(name);
    CANDY_CORE_ASSERT(it != passNameMap.end());
    SetActivePass(it->second, active);
  }
  
  RenderPass& RenderChain::operator[](uint32_t index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<renderPasses.size(), "Index out of bounds");
    return renderPasses[index];
  }
  const RenderPass& RenderChain::operator[](uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<renderPasses.size(), "Index out of bounds");
    return renderPasses[index];
  }
  const RenderPass& RenderChain::GetCurrentPass()const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[currentPassIndex];
  }
  
  RenderPass& RenderChain::GetFirstActivePass()
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[activePassIndices[0]];
  }
  RenderPass& RenderChain::GetLastActivePass()
  {
    return renderPasses[activePassIndices.back()];
  }
  
  const RenderPass& RenderChain::GetPassAt(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index];
  }
  std::string RenderChain::GetPassName(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index].GetName();
  }
  size_t RenderChain::GetTotalPassCount()const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses.size();
  }
  size_t RenderChain::GetActivePassCount()const
  {
    CANDY_PROFILE_FUNCTION();
    return activePasses.size();
  }
  bool RenderChain::IsPassActive(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return activePasses[index];
  }
  bool RenderChain::NextPass()
  {
    CANDY_PROFILE_FUNCTION();
    if (needsReset)
    {
      return false;
    }
    if (activePassIndex+1 >= activePassIndices.size())
    {
      End();
      needsReset=true;
      running=false;
      return false;
    }
    else
    {
      EndCurrentPass();
      activePassIndex++;
      currentPassIndex = activePassIndices[activePassIndex];
      BeginCurrentPass();
      return true;
    }
    
  }
  void RenderChain::SetActivePass(uint32_t index, bool active)
  {
    CANDY_CORE_ASSERT(index < renderPasses.size());
    activePasses[index] = active;
    needsActivePassUpdate=true;
  }
  void RenderChain::ActivatePass(uint32_t index)
  {
    SetActivePass(index, true);
  }
  void RenderChain::DisablePass(uint32_t index)
  {
    SetActivePass(index, false);
  }
  RenderPass& RenderChain::GetCurrentPass()
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[currentPassIndex];
  }
  RenderPass& RenderChain::GetPassAt(uint32_t index)
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index];
  }
  bool RenderChain::NeedsReset()const
  {
    return needsReset;
  }
  uint32_t RenderChain::AddPass(const std::string& name, const RenderPassConfig& config, bool startActive)
  {
    auto index = static_cast<uint32_t>(renderPasses.size());
    renderPasses.emplace_back(name, config);
    activePasses.push_back(startActive);
    passNameMap[name] = index;
    needsActivePassUpdate=true;
    return index;
  }
}