#pragma once
#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/StorageBuffer.hpp>
namespace Candy::Graphics
{
  class ShaderBufferManager
  {
  private:
    std::vector<VkDescriptorSet> descriptorSets;
    SharedPtr <UniformBuffer> uniformBuffer;
    SharedPtr <StorageBuffer> storageBuffer;
    SharedPtr <UniformBuffer> materialBuffer;
  };
}