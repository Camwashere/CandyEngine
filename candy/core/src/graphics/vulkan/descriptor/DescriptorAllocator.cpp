#include "candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
namespace Candy::Graphics
{
  DescriptorAllocator::DescriptorAllocator()
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    auto handle = GetHandle();
    return (handle.Allocate(layout, *set));
  }
  
  void DescriptorAllocator::Flip(uint32_t frameIndex)
  {
    CANDY_PROFILE_FUNCTION();
    pool->Flip(frameIndex);
  }
  
  void DescriptorAllocator::Destroy()
  {
    pool->Reset();
    pool.reset();
  }
  void DescriptorAllocator::Reset()
  {
    CANDY_PROFILE_FUNCTION();
    pool->Reset();
  }
  
}