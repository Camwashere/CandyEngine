#include "candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/GraphicsContext.hpp>
namespace Candy::Graphics
{
  DescriptorAllocator::DescriptorAllocator()
  {
    pool = DescriptorAllocatorPool::Create();
    //Vulkan::PushDeleter([=, this](){pool->Flip(); pool.reset();});
    //pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 2.);
    //Vulkan::PushDeleter([=, this](){Destroy();});
    pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 10.f);
    pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 10.f);
    pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 10.f);
    pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 10.f);
    
    
  }
  
  DescriptorAllocatorHandle DescriptorAllocator::GetHandle()
  {
    return pool->GetAllocator();
  }
  
  bool DescriptorAllocator::Allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout)
  {
    auto handle = GetHandle();
    return (handle.Allocate(layout, *set));
  }
  
  void DescriptorAllocator::Flip(uint32_t frameIndex)
  {
    pool->Flip(frameIndex);
  }
  void DescriptorAllocator::Reset()
  {
    pool->Reset();
  }
  
}