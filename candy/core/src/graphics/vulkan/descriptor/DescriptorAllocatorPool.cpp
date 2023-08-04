#include <candy/graphics/vulkan/descriptor/DescriptorAllocatorPool.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  bool IsMemoryError(VkResult errorResult) {
    switch (errorResult) {
      case VK_ERROR_FRAGMENTED_POOL:
      case VK_ERROR_OUT_OF_POOL_MEMORY:
        return true;
    }
    return false;
  }
  /*DescriptorAllocatorPool* DescriptorAllocatorPool::Create()
  {
    DescriptorAllocatorPool* impl = new DescriptorAllocatorPool();
    
    for (int i = 0; i < FRAME_OVERLAP; i++) {
      impl->descriptorPools.push_back(std::make_unique<PoolStorage>());
    }
    return impl;
  }*/
  UniquePtr<DescriptorAllocatorPool> DescriptorAllocatorPool::Create()
  {
    UniquePtr<DescriptorAllocatorPool> impl = CreateUniquePtr<DescriptorAllocatorPool>();
    
    for (int i = 0; i < FRAME_OVERLAP; i++) {
      impl->descriptorPools.push_back(std::make_unique<PoolStorage>());
    }
    return impl;
  }
  DescriptorAllocatorHandle::~DescriptorAllocatorHandle()
  {
    DescriptorAllocatorPool* implPool = static_cast<DescriptorAllocatorPool*>(ownerPool);
    if (implPool) {
      
      implPool->ReturnAllocator(*this, false);
    }
  }
  
  DescriptorAllocatorHandle::DescriptorAllocatorHandle(DescriptorAllocatorHandle&& other)
  {
    Return();
    
    vkPool = other.vkPool;
    poolIdx = other.poolIdx;
    ownerPool = other.ownerPool;
    
    other.ownerPool = nullptr;
    other.poolIdx = -1;
    other.vkPool = VkDescriptorPool{};
  }
  
  DescriptorAllocatorHandle& DescriptorAllocatorHandle::operator=(DescriptorAllocatorHandle&& other)
  {
    Return();
    
    vkPool = other.vkPool;
    poolIdx = other.poolIdx;
    ownerPool = other.ownerPool;
    
    other.ownerPool = nullptr;
    other.poolIdx = -1;
    other.vkPool = VkDescriptorPool{};
    
    return *this;
  }
  
  void DescriptorAllocatorHandle::Return()
  {
    DescriptorAllocatorPool* implPool = static_cast<DescriptorAllocatorPool*>(ownerPool);
    
    if (implPool) {
      implPool->ReturnAllocator(*this, false);
    }
    
    vkPool = VkDescriptorPool{ };
    poolIdx = -1;
    ownerPool = nullptr;
  }
  
  bool DescriptorAllocatorHandle::Allocate(const VkDescriptorSetLayout& layout, VkDescriptorSet& builtSet)
  {
    DescriptorAllocatorPool*implPool = static_cast<DescriptorAllocatorPool*>(ownerPool);
    
    
    VkDescriptorSetAllocateInfo allocInfo;
    allocInfo.pNext = nullptr;
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = vkPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &layout;
    
    VkResult result = vkAllocateDescriptorSets(Vulkan::LogicalDevice(), &allocInfo, &builtSet);
    if (result != VK_SUCCESS)
    {
      //we reallocate pools on memory error
      if (IsMemoryError(result))
      {
        //out of space need reallocate			
        
        implPool->ReturnAllocator(*this, true);
        
        DescriptorAllocatorHandle newHandle = implPool->GetAllocator();
        
        vkPool = newHandle.vkPool;
        poolIdx = newHandle.poolIdx;
        
        newHandle.vkPool = VkDescriptorPool{};
        newHandle.poolIdx = -1;
        newHandle.ownerPool = nullptr;
        //could be good idea to avoid infinite loop here
        return Allocate(layout, builtSet);
      }
      else {
        //stuff is truly broken
        return false;
      }
    }
    
    return true;
  }
  
  VkDescriptorPool DescriptorAllocatorPool::createPool(int count, VkDescriptorPoolCreateFlags flags)
  {
    std::vector<VkDescriptorPoolSize> sizes;
    sizes.reserve(poolSizes.sizes.size());
    for (auto sz : poolSizes.sizes) {
      sizes.push_back({ sz.type, uint32_t(sz.multiplier * count) });
    }
    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = flags;
    pool_info.maxSets = count;
    pool_info.poolSizeCount = (uint32_t)sizes.size();
    pool_info.pPoolSizes = sizes.data();
    
    VkDescriptorPool descriptorPool;
    vkCreateDescriptorPool(Vulkan::LogicalDevice(), &pool_info, nullptr, &descriptorPool);
    
    return descriptorPool;
  }
  
  DescriptorAllocatorPool::~DescriptorAllocatorPool()
  {
    for (VkDescriptorPool allocator : clearAllocators) {
      vkDestroyDescriptorPool(Vulkan::LogicalDevice(), allocator, nullptr);
    }
    for (auto&& storage : descriptorPools) {
      for (VkDescriptorPool allocator : storage->fullAllocators) {
        vkDestroyDescriptorPool(Vulkan::LogicalDevice(), allocator, nullptr);
      }
      for (VkDescriptorPool allocator : storage->usableAllocators) {
        vkDestroyDescriptorPool(Vulkan::LogicalDevice(), allocator, nullptr);
      }
    }
  }
  void DescriptorAllocatorPool::Reset()
  {
    for (uint32_t i=0; i<FRAME_OVERLAP; i++)
    {
      for (auto al :  descriptorPools[i]->fullAllocators ) {
        
        vkResetDescriptorPool(Vulkan::LogicalDevice(), al, VkDescriptorPoolResetFlags{ 0 });
        
        clearAllocators.push_back(al);
      }
      
      for (auto al : descriptorPools[i]->usableAllocators) {
        
        vkResetDescriptorPool(Vulkan::LogicalDevice(), al, VkDescriptorPoolResetFlags{ 0 });
        
        clearAllocators.push_back(al);
      }
      
      descriptorPools[i]->fullAllocators.clear();
      descriptorPools[i]->usableAllocators.clear();
    }
    
  }
  void DescriptorAllocatorPool::Flip(uint32_t newFrameIndex)
  {
    frameIndex = newFrameIndex;
    for (auto al :  descriptorPools[frameIndex]->fullAllocators ) {
      
      vkResetDescriptorPool(Vulkan::LogicalDevice(), al, VkDescriptorPoolResetFlags{ 0 });
      
      clearAllocators.push_back(al);
    }
    
    for (auto al : descriptorPools[frameIndex]->usableAllocators) {
      
      vkResetDescriptorPool(Vulkan::LogicalDevice(), al, VkDescriptorPoolResetFlags{ 0 });
      
      clearAllocators.push_back(al);
    }
    
    descriptorPools[frameIndex]->fullAllocators.clear();
    descriptorPools[frameIndex]->usableAllocators.clear();
  }
  
  void DescriptorAllocatorPool::SetPoolSizeMultiplier(VkDescriptorType type, float multiplier)
  {
    for (auto& s : poolSizes.sizes) {
      if (s.type == type) {
        s.multiplier = multiplier;
        return;
      }
    }
    
    //not found, so add it
    PoolSize newSize;
    newSize.type = type;
    newSize.multiplier = multiplier;
    poolSizes.sizes.push_back(newSize);
  }
  
  void DescriptorAllocatorPool::ReturnAllocator(DescriptorAllocatorHandle& handle, bool bIsFull)
  {
    std::lock_guard<std::mutex> lk(poolMutex);
    
    
    if (bIsFull) {
      descriptorPools[handle.poolIdx]->fullAllocators.push_back(VkDescriptorPool{ handle.vkPool });
    }
    else {
      descriptorPools[handle.poolIdx]->usableAllocators.push_back(VkDescriptorPool{ handle.vkPool });
    }
  }
  
  DescriptorAllocatorHandle DescriptorAllocatorPool::GetAllocator()
  {
    std::lock_guard<std::mutex> lk(poolMutex);
    
    
    bool foundAllocator = false;
    
    uint32_t poolIndex = frameIndex ;
    
    
    VkDescriptorPool allocator;
    //try reuse an allocated pool
    if (clearAllocators.size() != 0) {
      allocator = clearAllocators.back();
      clearAllocators.pop_back();
      foundAllocator = true;
    }
    else {
      if (descriptorPools[poolIndex]->usableAllocators.size() > 0) {
        allocator = descriptorPools[poolIndex]->usableAllocators.back();
        descriptorPools[poolIndex]->usableAllocators.pop_back();
        foundAllocator = 1;
      }
    }
    //need a new pool
    if (!foundAllocator)
    {
      //static pool has to be free-able
      VkDescriptorPoolCreateFlags flags = 0;
      if (poolIndex == 0) {
        flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
      }
      
      VkDescriptorPool newPool = createPool(2000, flags);
      
      allocator = newPool;
      
      foundAllocator = true;
    }
    
    DescriptorAllocatorHandle newHandle;
    newHandle.ownerPool = this;
    newHandle.poolIdx = poolIndex;
    newHandle.vkPool = allocator;
    
    return newHandle;
  }
}