#include <candy/graphics/FrameResources.hpp>
#include <candy/graphics/Renderer.hpp>
namespace Candy::Graphics
{
  VkDescriptorSet& FrameResources::GetDescriptorSet(uint32_t index)
  {
    return GetDescriptorSet(index, Renderer::GetCurrentPassIndex());
  }
  
  VkDescriptorSet& FrameResources::GetDescriptorSet(uint32_t index, uint8_t renderPassIndex)
  {
    if (index == MATERIAL_SET)
    {
      if (renderPassIndex == Renderer::overlayPassIndex)
      {
        return overlayDescriptorSet;
      }
    }
    return descriptorSets[index];
  }
  VkDescriptorSet& FrameResources::GlobalDescriptor() {return descriptorSets[GLOBAL_SET];}
  VkDescriptorSet& FrameResources::ObjectDescriptor() {return descriptorSets[OBJECT_SET];}
  VkDescriptorSet& FrameResources::MaterialDescriptor(){return GetDescriptorSet(MATERIAL_SET);}
}