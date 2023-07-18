#pragma once
#include "vulkan/vulkan.h"
#include <vector>
#include "../../ShaderUtils.hpp"
#include "Pipeline.hpp"
namespace Candy::Graphics
{
  
  class PipelineManager
  {
  private:
    std::vector<Pipeline> pipelines;
    uint32_t currentID=0;
    
  public:
    PipelineManager();
    
  public:
    void AddPipeline(Pipeline& pipeline);
  
  };
}