#pragma once
#include <vulkan/vulkan.h>
#include <candy/math/Vector.hpp>
#include <vector>
namespace Candy::Graphics
{
  enum class FrameBufferTextureFormat
  {
    None = 0,
    
    // Color
    RGBA8,
    RED_INTEGER,
    
    // Depth/stencil
    DEPTH24STENCIL8,
    
    // Defaults
    Depth = DEPTH24STENCIL8
  };
  struct FrameBufferTextureSpecification
  {
    FrameBufferTextureFormat textureFormat = FrameBufferTextureFormat::None;
    FrameBufferTextureSpecification() = default;
    FrameBufferTextureSpecification(FrameBufferTextureFormat format)
      : textureFormat(format) {}
    
    
  };
  
  struct FrameBufferSpecification
  {
    Math::Vector2u size;
    std::vector<FrameBufferTextureSpecification> attachments;
    uint32_t layers=1;
  };
  class FrameBuffer
  {
  private:
    VkFramebuffer buffer=VK_NULL_HANDLE;
    FrameBufferSpecification specification;
    std::vector<FrameBufferTextureSpecification> colorAttachmentSpecifications;
    FrameBufferTextureSpecification depthAttachmentSpecification{FrameBufferTextureFormat::None};
    std::vector<VkImageView> colorAttachments;
    VkImageView depthAttachment = VK_NULL_HANDLE;
    
  public:
    FrameBuffer(FrameBufferSpecification spec);
    ~FrameBuffer();
    
  
    
  public:
    /*void Invalidate();
    void Bind();
    void Unbind();
    void Resize(uint32_t width, uint32_t height);
    int ReadPixel(uint32_t attachmentIndex, int x, int y);
    void ClearAttachment(uint32_t attachmentIndex, int value);
    VkImageView GetColorAttachment(uint32_t index=0)const;
    
    FrameBufferSpecification GetSpecification()const;*/
  
    
  };
}