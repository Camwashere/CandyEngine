#include "candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/GraphicsContext.hpp>
namespace Candy::Graphics
{
  DescriptorAllocator::DescriptorAllocator(const VkDevice& logicalDevice)
  {
    pool = UniquePtr<vke::DescriptorAllocatorPool>(vke::DescriptorAllocatorPool::Create(logicalDevice, 1));
    //pool->SetPoolSizeMultiplier(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 2.);
    //Vulkan::PushDeleter([=, this](){Destroy();});
    
    
  }
  
  vke::DescriptorAllocatorHandle DescriptorAllocator::GetHandle()
  {
    return pool->GetAllocator();
  }
  
  bool DescriptorAllocator::Allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout)
  {
    auto handle = GetHandle();
    return (handle.Allocate(layout, *set));
  }
  
  void DescriptorAllocator::Flip()
  {
    pool->Flip();
  }
  
  void DescriptorAllocator::Destroy()
  {
    pool.reset();
  }
}