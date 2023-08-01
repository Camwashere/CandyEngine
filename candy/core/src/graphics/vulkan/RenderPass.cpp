#include <candy/graphics/vulkan/RenderPass.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/Renderer.hpp>
namespace Candy::Graphics
{
    RenderPass::RenderPass(VkFormat colorAttachmentFormat) : clearColor(Color::black)
    {
        
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = colorAttachmentFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
      
      VkAttachmentDescription depthAttachment{};
      depthAttachment.format = GraphicsContext::FindDepthFormat();
      depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
      depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
      
      VkAttachmentReference depthAttachmentRef{};
      depthAttachmentRef.attachment = 1;
      depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        
        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        
        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;
        
        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
      dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
      dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
      dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
      dependency.srcAccessMask = 0;
        
        
        std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;
        
        CANDY_CORE_ASSERT(vkCreateRenderPass(Vulkan::LogicalDevice(), &renderPassInfo, nullptr, &renderPass) == VK_SUCCESS, "Failed to create render pass!");
        Vulkan::DeletionQueue().Push(renderPass);
        //Vulkan::PushDeleter([=, this](){vkDestroyRenderPass(Vulkan::LogicalDevice(), renderPass, nullptr);});
    }
    
    RenderPass::~RenderPass()
    {
        //vkDestroyRenderPass(Vulkan::LogicalDevice(), renderPass, nullptr);
    }
    
    /*void RenderPass::Destroy()
    {
      vkDestroyRenderPass(Vulkan::LogicalDevice(), renderPass, nullptr);
      renderPass = VK_NULL_HANDLE;
    }*/
    
    
    
    VkRenderPassBeginInfo RenderPass::BeginPass(VkFramebuffer frameBuffer, VkExtent2D extent)
    {
        VkRenderPassBeginInfo beginPassInfo{};
        
        beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        beginPassInfo.renderPass = renderPass;
        beginPassInfo.framebuffer = frameBuffer;
        beginPassInfo.renderArea.offset = {offset.x, offset.y};
        beginPassInfo.renderArea.extent = extent;
        //VkClearValue clearColorVal = {{{clearColor.x, clearColor.y, clearColor.z, clearColor.w}}};
        VkClearValue clearColorVal = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        beginPassInfo.clearValueCount = 1;
        beginPassInfo.pClearValues = &clearColorVal;
        
        return beginPassInfo;
    }
    
}