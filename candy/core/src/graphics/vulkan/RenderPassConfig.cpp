#include <candy/graphics/vulkan/RenderPassConfig.hpp>
#include "CandyPch.hpp"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
namespace Candy::Graphics
{
  
  SubpassBuilder::SubpassBuilder(VkPipelineBindPoint bindPoint)
  {
    CANDY_PROFILE_FUNCTION();
    config.pipelineBindPoint = bindPoint;
  }
  SubpassBuilder& SubpassBuilder::AddColorAttachment(uint32_t attachmentIndex, VkImageLayout layout)
  {
    CANDY_PROFILE_FUNCTION();
    config.colorAttachments.emplace_back(attachmentIndex, layout);
    return *this;
  }
  SubpassBuilder& SubpassBuilder::SetDepthAttachment(uint32_t attachmentIndex, VkImageLayout layout)
  {
    CANDY_PROFILE_FUNCTION();
    config.depthAttachment = {attachmentIndex, layout};
    return *this;
  }
  SubpassBuilder& SubpassBuilder::AddInputAttachment(uint32_t attachmentIndex, VkImageLayout layout)
  {
    CANDY_PROFILE_FUNCTION();
    config.inputAttachments.emplace_back(attachmentIndex, layout);
    return *this;
  }
  SubpassBuilder& SubpassBuilder::AddPreserveAttachment(uint32_t attachmentIndex)
  {
    CANDY_PROFILE_FUNCTION();
    config.preserveAttachments.push_back(attachmentIndex);
    return *this;
  }
  
  PassAttachmentBuilder::PassAttachmentBuilder()=default;
  PassAttachmentBuilder::PassAttachmentBuilder(VkFormat formatValue, VkImageLayout initialLayoutValue, VkImageLayout finalLayoutValue) : format(formatValue), initialLayout(initialLayoutValue), finalLayout(finalLayoutValue)
  {
  
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetFormat(VkFormat value)
  {
    format = value;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetLayout(VkImageLayout initialLayoutValue, VkImageLayout finalLayoutValue)
  {
    initialLayout = initialLayoutValue;
    finalLayout = finalLayoutValue;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetLoadOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentLoadOp stencilLoadOpVal)
  {
    loadOp = mainLoadOp;
    stencilLoadOp = stencilLoadOpVal;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetStoreOps(VkAttachmentStoreOp mainStoreOp, VkAttachmentStoreOp stencilStoreOpVal)
  {
    storeOp = mainStoreOp;
    stencilStoreOp = stencilStoreOpVal;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetMainOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentStoreOp mainStoreOp)
  {
    loadOp = mainLoadOp;
    storeOp = mainStoreOp;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetStencilOps(VkAttachmentLoadOp stencilLoadOpVal, VkAttachmentStoreOp stencilStoreOpVal)
  {
    stencilLoadOp = stencilLoadOpVal;
    stencilStoreOp = stencilStoreOpVal;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentStoreOp mainStoreOp, VkAttachmentLoadOp stencilLoadOpVal, VkAttachmentStoreOp stencilStoreOpVal)
  {
    loadOp = mainLoadOp;
    storeOp = mainStoreOp;
    stencilLoadOp = stencilLoadOpVal;
    stencilStoreOp = stencilStoreOpVal;
    return *this;
  }
  PassAttachmentBuilder& PassAttachmentBuilder::SetSamples(VkSampleCountFlagBits value)
  {
    samples = value;
    return *this;
  }
  
  
  VkAttachmentDescription PassAttachmentBuilder::Build()
  {
    CANDY_PROFILE_FUNCTION();
    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.initialLayout = initialLayout;
    desc.finalLayout = finalLayout;
    desc.loadOp = loadOp;
    desc.storeOp = storeOp;
    desc.stencilLoadOp = stencilLoadOp;
    desc.stencilStoreOp = stencilStoreOp;
    return desc;
  }
  
  RenderPassBuilder& RenderPassBuilder::AddAttachment(VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout,
  VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp,
  VkSampleCountFlagBits samples)
  {
    VkAttachmentDescription desc{};
    desc.format = format;
    desc.samples = samples;
    desc.initialLayout = initialLayout;
    desc.finalLayout = finalLayout;
    desc.loadOp = loadOp;
    desc.storeOp = storeOp;
    desc.stencilLoadOp = stencilLoadOp;
    desc.stencilStoreOp = stencilStoreOp;
    config.attachments.push_back(desc);
    
    return *this;
    
  }
  
  RenderPassBuilder& RenderPassBuilder::AddAttachment(const VkAttachmentDescription& attachment)
  {
    config.attachments.push_back(attachment);
    return *this;
  }
  RenderPassBuilder& RenderPassBuilder::AddClearValue(VkClearValue value)
  {
    config.defaultClearValues.push_back(value);
    return *this;
  }
  RenderPassBuilder& RenderPassBuilder::AddStandardClearValues()
  {
    std::vector<VkClearValue> clearValues(2);
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
    clearValues[1].depthStencil = {1.0f, 0};
    config.defaultClearValues.push_back(clearValues[0]);
    config.defaultClearValues.push_back(clearValues[1]);
    return *this;
  }
  /*SubpassBuilder& RenderPassBuilder::AddSubpass(VkPipelineBindPoint bindPoint)
  {
    subpasses.emplace_back(bindPoint);
    return subpasses.back();
  }*/
 
  RenderPassBuilder& RenderPassBuilder::AddSubpass(const SubpassBuilder& subpass)
  {
    config.subpasses.push_back(subpass.config);
    return *this;
  }
  RenderPassBuilder& RenderPassBuilder::AddDefaultDependency()
  {
    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    dependency.srcAccessMask = 0;
    config.dependencies.push_back(dependency);
    return *this;
  }
  RenderPassBuilder& RenderPassBuilder::AddDependency(const VkSubpassDependency& dependency)
  {
    config.dependencies.push_back(dependency);
    return *this;
  }
  
  /*VkRenderPass RenderPassBuilder::Build()
  {
    CANDY_PROFILE_FUNCTION();
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
    renderPassInfo.pDependencies = dependencies.data();
    
    std::vector<VkSubpassDescription> subs;
    for (auto& subpass: subpasses)
    {
      VkSubpassDescription desc{};
      desc.pipelineBindPoint = subpass.pipelineBindPoint;
      desc.colorAttachmentCount = static_cast<uint32_t>(subpass.colorAttachments.size());
      desc.pColorAttachments = subpass.colorAttachments.data();
      desc.pDepthStencilAttachment = subpass.depthAttachment.has_value() ? &subpass.depthAttachment.value() : nullptr;
      desc.inputAttachmentCount = static_cast<uint32_t>(subpass.inputAttachments.size());
      desc.pInputAttachments = subpass.inputAttachments.data();
      desc.preserveAttachmentCount = static_cast<uint32_t>(subpass.preserveAttachments.size());
      desc.pPreserveAttachments = subpass.preserveAttachments.data();
      subs.push_back(desc);
    }
    renderPassInfo.subpassCount = static_cast<uint32_t>(subs.size());
    renderPassInfo.pSubpasses = subs.data();
    
    
    VkRenderPass renderPass;
    CANDY_VULKAN_CHECK(vkCreateRenderPass(Vulkan::LogicalDevice(), &renderPassInfo, nullptr, &renderPass));
    Vulkan::DeletionQueue().Push(renderPass);
    return renderPass;
  }*/
  
  RenderPassConfig RenderPassBuilder::GetConfig()const
  {
    return config;
  }
  
  RenderPassConfig RenderPassBuilder::FastBuild(VkFormat colorAttachmentFormat, VkImageLayout finalLayout)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<VkClearValue> clearValues(2);
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
    clearValues[1].depthStencil = {1.0f, 0};
    return RenderPassBuilder().AddAttachment
    (
      PassAttachmentBuilder(colorAttachmentFormat, VK_IMAGE_LAYOUT_UNDEFINED, finalLayout)
      .SetMainOps(VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE)
      .SetStencilOps(VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetSamples(VK_SAMPLE_COUNT_1_BIT).Build()
    )
    .AddAttachment
    (
      PassAttachmentBuilder(GraphicsContext::FindDepthFormat(), VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
      .SetMainOps(VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetStencilOps(VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE)
      .SetSamples(VK_SAMPLE_COUNT_1_BIT).Build()
    )
    .AddSubpass
    (
      SubpassBuilder(VK_PIPELINE_BIND_POINT_GRAPHICS)
      .AddColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
      .SetDepthAttachment(1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
    )
    .AddDefaultDependency()
    .AddClearValue(clearValues[0])
    .AddClearValue(clearValues[1])
    .GetConfig();
  }
}