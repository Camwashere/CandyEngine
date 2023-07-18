#include <candy/graphics/vulkan/pipeline/PipelineManager.hpp>

namespace Candy::Graphics
{
  PipelineManager::PipelineManager() : pipelines()
  {
  
  }
  
  void PipelineManager::AddPipeline(Candy::Graphics::Pipeline &pipeline)
  {
    pipeline.id = currentID;
    pipelines.push_back(pipeline);
  }
}