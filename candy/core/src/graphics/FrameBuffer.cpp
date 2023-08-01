#include <candy/graphics/FrameBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
namespace Candy::Graphics
{
  static bool IsDepthFormat(FrameBufferTextureFormat format)
  {
    switch (format)
    {
      case FrameBufferTextureFormat::DEPTH24STENCIL8:  return true;
    }
    
    return false;
  }
  FrameBuffer::FrameBuffer(FrameBufferSpecification spec) : specification(std::move(spec))
  {
    for (auto s : specification.attachments)
    {
      if (!IsDepthFormat(s.textureFormat))
      {
        colorAttachmentSpecifications.emplace_back(s);
      }
      else
      {
        depthAttachmentSpecification = s;
      }
      
    }
    //Invalidate();
  }
}