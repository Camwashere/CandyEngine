#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <optional>
#include <string>
namespace Candy::Graphics
{
  struct SubpassConfig
  {
    VkPipelineBindPoint pipelineBindPoint;
    std::vector<VkAttachmentReference> colorAttachments;
    std::optional<VkAttachmentReference> depthAttachment;
    std::vector<VkAttachmentReference> inputAttachments;
    std::vector<uint32_t> preserveAttachments;
  };
  struct RenderPassConfig
  {
    std::vector<VkAttachmentDescription> attachments;
    std::vector<SubpassConfig> subpasses;
    std::vector<VkSubpassDependency> dependencies;
    
    std::vector<VkClearValue> defaultClearValues;
    
    bool needsUniqueFrameBuffer=false;
  };
  class RenderPassBuilder;
 
  class SubpassBuilder
  {
  private:
    SubpassConfig config;
    
    
  public:
    explicit SubpassBuilder(VkPipelineBindPoint bindPoint);
    SubpassBuilder& AddColorAttachment(uint32_t attachmentIndex, VkImageLayout layout);
    SubpassBuilder& SetDepthAttachment(uint32_t attachmentIndex, VkImageLayout layout);
    SubpassBuilder& AddInputAttachment(uint32_t attachmentIndex, VkImageLayout layout);
    SubpassBuilder& AddPreserveAttachment(uint32_t attachmentIndex);
    
    friend class RenderPassBuilder;
  };
  class PassAttachmentBuilder
  {
  private:
    VkFormat format=VK_FORMAT_UNDEFINED;
    VkImageLayout initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    VkImageLayout finalLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    VkAttachmentLoadOp loadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    VkAttachmentStoreOp storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    VkAttachmentLoadOp stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    VkAttachmentStoreOp stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    VkSampleCountFlagBits samples=VK_SAMPLE_COUNT_1_BIT;
    
  public:
    PassAttachmentBuilder();
    PassAttachmentBuilder(VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout);
    PassAttachmentBuilder& SetFormat(VkFormat format);
    PassAttachmentBuilder& SetLayout(VkImageLayout initialLayout, VkImageLayout finalLayout);
    PassAttachmentBuilder& SetLoadOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentLoadOp stencilLoadOp);
    PassAttachmentBuilder& SetStoreOps(VkAttachmentStoreOp mainStoreOp, VkAttachmentStoreOp stencilStoreOp);
    PassAttachmentBuilder& SetMainOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentStoreOp mainStoreOp);
    PassAttachmentBuilder& SetStencilOps(VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp);
    PassAttachmentBuilder& SetOps(VkAttachmentLoadOp mainLoadOp, VkAttachmentStoreOp mainStoreOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp);
    PassAttachmentBuilder& SetSamples(VkSampleCountFlagBits samples);
    
    VkAttachmentDescription Build();
    
    friend class RenderPassBuilder;
  
  };
  class RenderPassBuilder
  {
  private:
    /*std::vector<VkAttachmentDescription> attachments;
    std::vector<SubpassBuilder> subpasses;
    std::vector<VkSubpassDependency> dependencies;*/
    RenderPassConfig config;
    
  public:
    RenderPassBuilder& AddAttachment(VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout,
    VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp,
    VkSampleCountFlagBits samples=VK_SAMPLE_COUNT_1_BIT);
    
    RenderPassBuilder& AddAttachment(const VkAttachmentDescription& attachment);
    
    RenderPassBuilder& AddClearValue(VkClearValue value);
    
    RenderPassBuilder& AddStandardClearValues();
    
    RenderPassBuilder& AddSubpass(const SubpassBuilder& subpass);
    
    RenderPassBuilder& AddDefaultDependency();
    RenderPassBuilder& AddDependency(const VkSubpassDependency& dependency);
    
    //VkRenderPass Build();
    [[nodiscard]] RenderPassConfig GetConfig()const;
    
  public:
    static RenderPassConfig FastBuild(VkFormat colorAttachmentFormat, VkImageLayout finalLayout);
    
    
  };
}