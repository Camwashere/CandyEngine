#pragma once
#include <vulkan/vulkan.h>
#include "device/VulkanDeviceManager.hpp"
#include <Candy/Math/Vector.hpp>
#include "../Color.hpp"
namespace Candy::Graphics
{
    class RenderPass
    {
    private:
        VkRenderPass renderPass;
        Math::Vector2i offset = {0, 0};
        Color clearColor;
   
    public:
        explicit RenderPass(VkFormat colorAttachmentFormat);
        ~RenderPass();
        
    public:
        operator VkRenderPass()const{return renderPass;}
        operator VkRenderPass(){return renderPass;}
        
        
    public:
        [[nodiscard]] VkRenderPassBeginInfo BeginPass(VkFramebuffer frameBuffer, VkExtent2D extent);
        void Destroy();
        
    };
}