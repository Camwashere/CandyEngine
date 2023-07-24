#include <candy/graphics/vulkan/DescriptorAllocator.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/GraphicsContext.hpp>
namespace Candy::Graphics
{
  DescriptorAllocator::DescriptorAllocator()
  {
    pool = UniquePtr<vke::DescriptorAllocatorPool>(vke::DescriptorAllocatorPool::Create(Vulkan::LogicalDevice(), FRAME_OVERLAP));
    //descriptorAllocatorPool->SetPoolSizeMultiplier()
    pool->GetAllocator();
    
    
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