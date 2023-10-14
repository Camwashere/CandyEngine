#include <candy/graphics/vulkan/RenderPass.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>
#include <utility>
#include "candy/graphics/RenderCommand.hpp"

namespace Candy::Graphics
{
  RenderPass::RenderPass(std::string  passName, RenderPassConfig  configuration) : name(std::move(passName)), config(std::move(configuration))
  {
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(config.attachments.size());
    renderPassInfo.pAttachments = config.attachments.data();
    renderPassInfo.dependencyCount = static_cast<uint32_t>(config.dependencies.size());
    renderPassInfo.pDependencies = config.dependencies.data();
    
    std::vector<VkSubpassDescription> subs;
    for (const auto& subpass : config.subpasses)
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
    CANDY_VULKAN_CHECK(vkCreateRenderPass(Vulkan::LogicalDevice(), &renderPassInfo, nullptr, &renderPass));
    Vulkan::DeletionQueue().Push(renderPass);
    
    clearValues = config.defaultClearValues;
  }
  
  RenderPass::operator VkRenderPass(){return renderPass;}
  RenderPass::operator VkRenderPass()const{return renderPass;}
  
  const std::vector<VkClearValue>& RenderPass::GetClearValues()const
  {
    return clearValues;
  }
  void RenderPass::SetRenderTarget(RenderTarget& target)
  {
    currentTarget = &target;
  }
  RenderTarget* RenderPass::GetCurrentTarget()
  {
    return currentTarget;
  }
  void RenderPass::SetClearValues(const std::vector<VkClearValue>& values)
  {
    clearValues = values;
  }
  void RenderPass::Begin()
  {
    state = RenderPassState::Running;
  }
  void RenderPass::End()
  {
    state = RenderPassState::Stopped;
    
  }
  
  bool RenderPass::IsRunning()const
  {
    return state==RenderPassState::Running;
  }
  bool RenderPass::IsStopped()const
  {
    return state==RenderPassState::Stopped;
  }
  RenderPassState RenderPass::GetCurrentState()const
  {
    return state;
  }
  RenderPassConfig RenderPass::GetConfig()const
  {
    return config;
  }
  
  std::string RenderPass::GetName()const {return name;}
  bool RenderPass::NeedsUniqueFrameBuffer()const {return config.needsUniqueFrameBuffer;}
  
}