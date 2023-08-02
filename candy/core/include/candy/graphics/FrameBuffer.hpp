#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <vector>
namespace Candy::Graphics
{
 
  class FrameBuffer
  {
  private:
    VkFramebuffer buffer=VK_NULL_HANDLE;
    VkRenderPass renderPass = VK_NULL_HANDLE;
    Math::Vector2u size;
    uint32_t layers;
    std::vector<VkImageView> attachments;


    
  public:
    FrameBuffer();
    FrameBuffer(VkRenderPass renderPass, Math::Vector2u size, const std::vector<VkImageView>& attachments, uint32_t layers=1);
    
    void Set(VkRenderPass renderPass, Math::Vector2u size, const std::vector<VkImageView>& attachments, uint32_t layers=1);
    
  
    
  public:
    operator VkFramebuffer(){return buffer;}
    operator VkFramebuffer()const{return buffer;}
  
    
  };
}