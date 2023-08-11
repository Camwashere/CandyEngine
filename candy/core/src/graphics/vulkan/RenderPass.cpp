#include <candy/graphics/vulkan/RenderPass.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/Renderer.hpp>

namespace Candy::Graphics
{
  
  RenderPass::RenderPass(const VkAttachmentDescription& depthAttachment, const std::vector<VkAttachmentDescription>& colorAttachments,
                         const std::vector<VkAttachmentDescription>& inputAttachments)
  {
    std::vector<VkAttachmentDescription> attachments{};
    attachments.resize(colorAttachments.size() + 1 + inputAttachments.size());
    
    for (size_t i = 0; i < colorAttachments.size(); i++)
    {
      attachments[i] = colorAttachments[i];
    }
    
    for (size_t i = 0; i < inputAttachments.size(); i++)
    {
      attachments[i + colorAttachments.size()] = inputAttachments[i];
    }
    
    attachments[attachments.size() - 1] = depthAttachment;
    
    VkAttachmentReference depthRef{};
    depthRef.attachment = attachments.size() - 1;
    depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    
    std::vector<VkAttachmentReference> colorRefs{};
    colorRefs.resize(colorAttachments.size());
    
    for (size_t i=0; i<colorRefs.size(); i++)
    {
      colorRefs[i].attachment = i;
      colorRefs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    
    std::vector<VkAttachmentReference> inputRefs{};
    inputRefs.resize(inputAttachments.size());
    
    for (size_t i=0; i<inputRefs.size(); i++)
    {
      inputRefs[i].attachment = i + colorAttachments.size();
      inputRefs[i].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }
    
    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = colorRefs.size();
    subpass.pColorAttachments = colorRefs.data();
    subpass.pDepthStencilAttachment = &depthRef;
    subpass.inputAttachmentCount=inputRefs.size();
    subpass.pInputAttachments=inputRefs.data();
    subpass.preserveAttachmentCount=0;
    subpass.pPreserveAttachments=nullptr;
    
    
    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    dependency.srcAccessMask = 0;
    
    
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
  }
  
  
  RenderPass::RenderPass(VkFormat colorAttachmentFormat, VkImageLayout finalLayout) : clearColor(Color::black)
  {
    
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = colorAttachmentFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = finalLayout;
    //colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    
    
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
    subpass.inputAttachmentCount=0;
    subpass.pInputAttachments=nullptr;
    subpass.preserveAttachmentCount=0;
    subpass.pPreserveAttachments=nullptr;
    
    
    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT|VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
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
    
  }
  
  RenderPass::~RenderPass()
  {
    //vkDestroyRenderPass(Vulkan::LogicalDevice(), renderPass, nullptr);
  }
  
  
  void RenderPass::SetClearColor(Color color)
  {
    clearColor = color;
    clearValues[0].color = {color.r, color.g, color.b, 1.0f};
  }
  void RenderPass::SetDepthStencil(float depth, uint32_t stencil)
  {
    clearValues[1].depthStencil.depth = depth;
    clearValues[1].depthStencil.stencil = stencil;
  }
  Color RenderPass::GetClearColor()const
  {
    return clearColor;
  }
  VkRenderPassBeginInfo RenderPass::BeginPass(FrameBuffer& frameBuffer, Math::Vector2u size)
  {
    VkRenderPassBeginInfo beginPassInfo{};
    
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = renderPass;
    beginPassInfo.framebuffer = frameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = size.width;
    beginPassInfo.renderArea.extent.height = size.height;
    //VkClearValue clearColorVal = {{{clearColor.x, clearColor.y, clearColor.z, clearColor.w}}};
    VkClearValue clearColorVal = {{{clearColor.x, clearColor.y, clearColor.z, 1.0f}}};
    beginPassInfo.clearValueCount = 1;
    beginPassInfo.pClearValues = &clearColorVal;
    
    return beginPassInfo;
  }
  VkRenderPassBeginInfo RenderPass::BeginPass(FrameBuffer& frameBuffer, VkExtent2D extent)
  {
    VkRenderPassBeginInfo beginPassInfo{};
    
    beginPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    beginPassInfo.renderPass = renderPass;
    beginPassInfo.framebuffer = frameBuffer;
    beginPassInfo.renderArea.offset.x = 0;
    beginPassInfo.renderArea.offset.y = 0;
    beginPassInfo.renderArea.extent.width = extent.width;
    beginPassInfo.renderArea.extent.height = extent.height;
    //VkClearValue clearColorVal = {{{clearColor.x, clearColor.y, clearColor.z, clearColor.w}}};
    VkClearValue clearColorVal = {{{clearColor.x, clearColor.y, clearColor.z, 1.0f}}};
    beginPassInfo.clearValueCount = 1;
    beginPassInfo.pClearValues = &clearColorVal;
    
    return beginPassInfo;
  }
  
}