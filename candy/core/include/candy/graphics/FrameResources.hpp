#pragma once
#include <candy/graphics/vulkan/CommandPool.hpp>
#include <array>
#include <candy/graphics/UniformBuffer.hpp>
#include <candy/graphics/StorageBuffer.hpp>
#include <candy/graphics/vulkan/Image.hpp>
#include <candy/graphics/vulkan/ImageView.hpp>
#include <candy/graphics/FrameBuffer.hpp>
#include <candy/graphics/PixelBuffer.hpp>
#include <candy/graphics/vulkan/RenderTarget.hpp>
namespace Candy::Graphics
{
  
  static constexpr unsigned int MAX_OBJECTS = 100;
  static constexpr int GLOBAL_SET = 0;
  static constexpr int OBJECT_SET = 1;
  static constexpr int MATERIAL_SET = 2;
  
  
  struct FrameResources
  {
    VkSemaphore renderSemaphore = VK_NULL_HANDLE;
    VkSemaphore presentSemaphore = VK_NULL_HANDLE;
    VkSemaphore computeSemaphore = VK_NULL_HANDLE;
    VkSemaphore transferSemaphore = VK_NULL_HANDLE;
    CommandPool commandPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkDescriptorSet viewportDescriptor = VK_NULL_HANDLE;
    VkDescriptorSet overlayDescriptorSet;
    SharedPtr <UniformBuffer> uniformBuffer;
    SharedPtr <StorageBuffer> storageBuffer;
    SharedPtr <UniformBuffer> materialBuffer;
    
    VkDescriptorSet& GlobalDescriptor();
    VkDescriptorSet& ObjectDescriptor();
    VkDescriptorSet& MaterialDescriptor();
    VkDescriptorSet& GetDescriptorSet(uint32_t index);
    VkDescriptorSet& GetDescriptorSet(uint32_t index, uint8_t renderPassIndex);
    
  };
}