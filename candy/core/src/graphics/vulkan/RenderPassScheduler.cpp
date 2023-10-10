#include <candy/graphics/vulkan/RenderPassScheduler.hpp>
#include "CandyPch.hpp"
#include <candy/graphics/vulkan/RenderPassConfig.hpp>
namespace Candy::Graphics
{
  
  
  
  bool RenderPassScheduler::Begin()
  {
    if (needsActivePassUpdate)
    {
      UpdateActivePasses();
    }
    ResetPassIndex();
    if (activePassIndices.empty())
    {
      running = false;
      return false;
    }
    running=true;
    renderPasses[currentPassIndex].Begin();
    return true;
  }
  bool RenderPassScheduler::End()
  {
    if (activePassIndex == activePassIndices.size()-1)
    {
      renderPasses[currentPassIndex].End();
      running = false;
      return true;
    }
    else
    {
      renderPasses[currentPassIndex].End();
      running = false;
      return false;
    }
  }
  void RenderPassScheduler::UpdateActivePasses()
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
  void RenderPassScheduler::ResetPassIndex()
  {
    activePassIndex=0;
    currentPassIndex=activePassIndices[activePassIndex];
  }
  bool RenderPassScheduler::IncrementActivePassIndex()
  {
    if (activePassIndex+1 >= activePassIndices.size())
    {
      activePassIndex = 0;
      currentPassIndex = activePassIndices[activePassIndex];
      return false;
    }
    else
    {
      activePassIndex++;
      currentPassIndex = activePassIndices[activePassIndex];
      return true;
    }
  }
  
  
  
  
  RenderPass& RenderPassScheduler::operator[](uint32_t index)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<renderPasses.size(), "Index out of bounds");
    return renderPasses[index];
  }
  const RenderPass& RenderPassScheduler::operator[](uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(index<renderPasses.size(), "Index out of bounds");
    return renderPasses[index];
  }
  const RenderPass& RenderPassScheduler::GetCurrentPass()const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[currentPassIndex];
  }
  const RenderPass& RenderPassScheduler::GetPassAt(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index];
  }
  std::string RenderPassScheduler::GetPassName(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index].GetName();
  }
  size_t RenderPassScheduler::GetTotalPassCount()const
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses.size();
  }
  size_t RenderPassScheduler::GetActivePassCount()const
  {
    CANDY_PROFILE_FUNCTION();
    return activePasses.size();
  }
  bool RenderPassScheduler::IsPassActive(uint32_t index)const
  {
    CANDY_PROFILE_FUNCTION();
    return activePasses[index];
  }
  bool RenderPassScheduler::NextPass()
  {
    CANDY_PROFILE_FUNCTION();
    return IncrementActivePassIndex();
    
  }
  void RenderPassScheduler::SetActivePass(uint32_t index, bool active)
  {
    CANDY_CORE_ASSERT(index < renderPasses.size());
    activePasses[index] = active;
    needsActivePassUpdate=true;
  }
  void RenderPassScheduler::ActivatePass(uint32_t index)
  {
    SetActivePass(index, true);
  }
  void RenderPassScheduler::DisablePass(uint32_t index)
  {
    SetActivePass(index, false);
  }
  RenderPass& RenderPassScheduler::GetCurrentPass()
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[currentPassIndex];
  }
  RenderPass& RenderPassScheduler::GetPassAt(uint32_t index)
  {
    CANDY_PROFILE_FUNCTION();
    return renderPasses[index];
  }
  
  uint32_t RenderPassScheduler::AddPass(const std::string& name, const RenderPassConfig& config, bool startActive)
  {
    auto index = static_cast<uint32_t>(renderPasses.size());
    renderPasses.emplace_back(name, config);
    activePasses.push_back(startActive);
    needsActivePassUpdate=true;
    return index;
  }
}