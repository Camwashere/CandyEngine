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
  
  };
}