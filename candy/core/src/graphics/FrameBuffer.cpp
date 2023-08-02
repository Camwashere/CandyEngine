#include <candy/graphics/FrameBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <utility>
namespace Candy::Graphics
{
  FrameBuffer::FrameBuffer() : renderPass(VK_NULL_HANDLE), size(0, 0), layers(1)
  {
  
  }
  FrameBuffer::FrameBuffer(VkRenderPass pass, Math::Vector2u bufferSize, const std::vector<VkImageView>& bufferAttachments, uint32_t bufferLayers) : renderPass(pass), size(bufferSize), attachments(bufferAttachments), layers(bufferLayers)
  {
    VkFramebufferCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.height = size.height;
    createInfo.width = size.width;
    createInfo.layers = layers;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    createInfo.renderPass = renderPass;
    
    vkCreateFramebuffer(Vulkan::LogicalDevice(), &createInfo, nullptr, &buffer);
  }
  
  void FrameBuffer::Set(VkRenderPass pass, Math::Vector2u bufferSize, const std::vector<VkImageView>& bufferAttachments, uint32_t bufferLayers)
  {
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
    createInfo.renderPass = renderPass;
    
    vkCreateFramebuffer(Vulkan::LogicalDevice(), &createInfo, nullptr, &buffer);
    
    Vulkan::DeletionQueue().Push(this);
  }
  

  

}