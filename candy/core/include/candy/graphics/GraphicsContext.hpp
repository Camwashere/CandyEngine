#pragma once

#include "CandyPch.hpp"
#include <vector>
#include <string>
#include "vulkan/VulkanDebugManager.hpp"
#include <optional>
#include "vulkan/device/VulkanDeviceManager.hpp"
#include "vulkan/SwapChain.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "vulkan/CommandBuffer.hpp"
#include "vulkan/RenderPass.hpp"
#include "vma/vk_mem_alloc.h"
#include "candy/graphics/shader/Shader.hpp"
#include "UniformBuffer.hpp"
#include <candy/event/Events.hpp>


struct GLFWwindow;
namespace Candy::Graphics
{
    static constexpr unsigned int FRAME_OVERLAP = 2;
  
    struct FrameData
    {
      VkSemaphore renderSemaphore=VK_NULL_HANDLE;
      VkSemaphore presentSemaphore=VK_NULL_HANDLE;
      VkFence renderFence=VK_NULL_HANDLE;
      CommandBuffer commandBuffer;
      VkDescriptorSet globalDescriptor=VK_NULL_HANDLE;
      SharedPtr<UniformBuffer> uniformBuffer;
    };
    
    
    class GraphicsContext
    {
    
    private:
        GLFWwindow* handle;
        VkSurfaceKHR surface=VK_NULL_HANDLE;
        UniquePtr<SwapChain> swapChain;
        //UniquePtr<RenderPass> renderPass;
        uint32_t currentFrameIndex = 0;
        uint32_t previousFrameIndex=0;
        FrameData frames[FRAME_OVERLAP];
        
        bool frameBufferResized=false;
        
    

        
    private:
        void InitSyncStructures();
        //VkRenderPassBeginInfo BeginRenderPass();
        void UpdateFrameIndex();
    public:
        explicit GraphicsContext(GLFWwindow* windowHandle);
        
    public:
        void SwapBuffers();
        void Present();
        void RebuildSwapChain(VkRenderPass renderPass);
        void OnFrameBufferResize(Events::FrameBufferResizeEvent& event);
        void CleanSwapChain();
        SwapChain& GetSwapChain();
        //VkRenderPass GetRenderPass();
        VkSurfaceKHR GetSurface();
        VkSurfaceFormatKHR GetSurfaceFormat();
        
        
        [[nodiscard]] uint32_t GetCurrentFrameIndex()const;
        [[nodiscard]] uint32_t GetPreviousFrameIndex()const;
        
        FrameData& GetCurrentFrame();
        FrameData& GetFrame(uint32_t index);
        FrameData& GetPreviousFrame();
        
        
    public:
      static UniquePtr<GraphicsContext> Create(GLFWwindow* windowHandle);
      static bool HasStencilComponent(VkFormat format);
      static VkFormat FindDepthFormat();
      static VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        
    private:
        friend class VulkanDebugManager;
        friend class VulkanDeviceManager;
        friend class VertexBuffer;
        friend class IndexBuffer;
        friend class SwapChain;
        friend class Renderer;
        friend class Vulkan;
        
    };
}