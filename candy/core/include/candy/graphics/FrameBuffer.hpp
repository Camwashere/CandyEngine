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
    Math::Vector2u offset = {0, 0};
    Math::Vector2u size;
    uint32_t layers;
    std::vector<VkImageView> attachments;


    
  public:
    FrameBuffer();
    
    void Bind();
    void Set(VkRenderPass renderPass, Math::Vector2u size, const std::vector<VkImageView>& attachments, uint32_t layers=1);
    
    [[nodiscard]] bool IsValid()const{return buffer !=VK_NULL_HANDLE;}
    void SetSize(Math::Vector2u size);
    void SetOffset(Math::Vector2u offset);
    [[nodiscard]] uint32_t GetWidth()const;
    [[nodiscard]] uint32_t GetHeight()const;
    [[nodiscard]] uint32_t GetOffsetX()const;
    [[nodiscard]] uint32_t GetOffsetY()const;
    [[nodiscard]] Math::Vector2u GetOffset()const;
    [[nodiscard]] Math::Vector2u GetSize()const;
  
    
  public:
    operator VkFramebuffer(){return buffer;}
    operator VkFramebuffer()const{return buffer;}
  
    
  };
}