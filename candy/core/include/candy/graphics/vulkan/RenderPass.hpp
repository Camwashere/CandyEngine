#pragma once
#include <vulkan/vulkan.h>
#include "device/VulkanDeviceManager.hpp"
#include <Candy/Math/Vector.hpp>
#include "../Color.hpp"
#include "../FrameBuffer.hpp"
#include <array>
namespace Candy::Graphics
{
  
  
  enum class RenderPassType
  {
    None=0,
    Overlay2D=1,
  };
    class RenderPass
    {
    private:
        VkRenderPass renderPass=VK_NULL_HANDLE;
        std::array<VkClearValue, 2> clearValues;
        Color clearColor;
        RenderPassType type=RenderPassType::None;
   
    public:
      RenderPass(VkFormat colorAttachmentFormat, RenderPassType passType);
      explicit RenderPass(const VkAttachmentDescription& depthAttachment, const std::vector<VkAttachmentDescription>& colorAttachments,const std::vector<VkAttachmentDescription>& inputAttachments);
        explicit RenderPass(VkFormat colorAttachmentFormat, VkImageLayout finalLayout);
        explicit RenderPass(VkFormat colorAttachmentFormat, VkFormat selectionAttachmentFormat, VkImageLayout finalLayout);
        ~RenderPass();
        
    public:
        operator VkRenderPass()const{return renderPass;}
        operator VkRenderPass(){return renderPass;}
        
        [[nodiscard]] bool IsValid()const{return renderPass != VK_NULL_HANDLE;}
        
        
    public:
      void SetClearColor(Color color);
      void SetDepthStencil(float depth, uint32_t stencil);
      Color GetClearColor()const;
      VkRenderPassBeginInfo BeginPass(FrameBuffer& frameBuffer, Math::Vector2u size);
        [[nodiscard]] VkRenderPassBeginInfo BeginPass(FrameBuffer& frameBuffer, VkExtent2D extent);
        //void Destroy();
        
    private:
      //friend class Renderer;
        
    };
}