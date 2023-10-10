#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
  
  
  class DescriptorAllocatorPool;
  
  struct DescriptorAllocatorHandle {
    friend class DescriptorAllocatorPool;
    DescriptorAllocatorHandle() = default;
    DescriptorAllocatorHandle& operator=(const DescriptorAllocatorHandle&) = delete;
    
    ~DescriptorAllocatorHandle();
    DescriptorAllocatorHandle(DescriptorAllocatorHandle&& other);
    DescriptorAllocatorHandle& operator=(DescriptorAllocatorHandle&& other);
    
    //return this handle to the pool. Will make this handle orphaned
    void Return();
    
    //allocate new descriptor. handle has to be valid
    //returns true if allocation succeeded, and false if it didnt
    //will mutate the handle if it requires a new vkDescriptorPool
    bool Allocate(const VkDescriptorSetLayout& layout, VkDescriptorSet& builtSet);
    
    
    DescriptorAllocatorPool* ownerPool{nullptr};
    VkDescriptorPool vkPool;
    int8_t poolIdx;
  };
  class DescriptorAllocatorPool {
  
  private:
    uint32_t frameIndex;
  
  public:
    struct PoolStorage {
      
      std::vector<VkDescriptorPool> usableAllocators;
      std::vector<VkDescriptorPool> fullAllocators;
    };
    
    struct PoolSize {
      VkDescriptorType type;
      float multiplier;
    };
    struct PoolSizes {
      std::vector<PoolSize> sizes =
      {
      { VK_DESCRIPTOR_TYPE_SAMPLER, 1.f },
      { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4.f },
      { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 4.f },
      { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1.f },
      { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1.f },
      { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1.f },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 2.f },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 2.f },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1.f },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1.f },
      { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1.f }
      };
    };
  public:
    DescriptorAllocatorPool()=default;
    ~DescriptorAllocatorPool();
    
    
    //static DescriptorAllocatorPool* Create();
    static UniquePtr<DescriptorAllocatorPool> Create();
    
    
    
    void Reset();
    
    //not thread safe
    //switches default allocators to the next frame. When frames loop it will reset the descriptors of that frame
    void Flip(uint32_t newFrameIndex);
    
    //not thread safe
    //override the pool size for a specific descriptor type. This will be used new pools are allocated
    void SetPoolSizeMultiplier(VkDescriptorType type, float multiplier);
    
    //thread safe, uses lock
    //get handle to use when allocating descriptors
    DescriptorAllocatorHandle GetAllocator();
    
    void ReturnAllocator(DescriptorAllocatorHandle& handle, bool bIsFull);
    VkDescriptorPool createPool(int count, VkDescriptorPoolCreateFlags flags);
    

    PoolSizes poolSizes;

    
    std::mutex poolMutex;
    
    //zero is for static pool, next is for frame indexing
    std::vector<UniquePtr<PoolStorage>> descriptorPools;
    
    //fully cleared allocators
    std::vector<VkDescriptorPool> clearAllocators;
  };
}