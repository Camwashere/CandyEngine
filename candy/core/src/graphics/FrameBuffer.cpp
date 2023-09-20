#include <candy/graphics/FrameBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
namespace Candy::Graphics
{
  FrameBuffer::FrameBuffer() : size(0, 0), layers(1)
  {
  
  }
  FrameBuffer::FrameBuffer(VkRenderPass pass, Math::Vector2u bufferSize, const std::vector<VkImageView>& bufferAttachments, uint32_t bufferLayers) : size(bufferSize), attachments(bufferAttachments), layers(bufferLayers)
  {
    CANDY_PROFILE_FUNCTION();
    renderPass = pass;
    VkFramebufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.height = size.height;
    createInfo.width = size.width;
    createInfo.layers = layers;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    createInfo.renderPass = pass;
    
    vkCreateFramebuffer(Vulkan::LogicalDevice(), &createInfo, nullptr, &buffer);
  }
  
  void FrameBuffer::Set(VkRenderPass pass, Math::Vector2u bufferSize, const std::vector<VkImageView>& bufferAttachments, uint32_t bufferLayers)
  {
    CANDY_PROFILE_FUNCTION();
    renderPass = pass;
    size = bufferSize;
    attachments = bufferAttachments;
    layers = bufferLayers;
    
    VkFramebufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.height = size.height;
    createInfo.width = size.width;
    createInfo.layers = layers;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    
    createInfo.renderPass = pass;
    
    vkCreateFramebuffer(Vulkan::LogicalDevice(), &createInfo, nullptr, &buffer);
    
    Vulkan::DeletionQueue().Push(this);
  }
  void FrameBuffer::Bind()
  {
    CANDY_PROFILE_FUNCTION();
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = buffer;
    
  }
  void FrameBuffer::SetSize(Math::Vector2u sizeV)
  {
    size = sizeV;
  }
  void FrameBuffer::SetOffset(Math::Vector2u offsetV)
  {
    offset = offsetV;
  }
  uint32_t FrameBuffer::GetWidth()const{return size.width;}
  uint32_t FrameBuffer::GetHeight()const{return size.height;}
  uint32_t FrameBuffer::GetOffsetX()const{return offset.x;}
  uint32_t FrameBuffer::GetOffsetY()const{return offset.y;}
  Math::Vector2u FrameBuffer::GetOffset()const{return offset;}
  Math::Vector2u FrameBuffer::GetSize()const{return size;}
  

  

}