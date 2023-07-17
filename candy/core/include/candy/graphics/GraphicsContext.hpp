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
#include "vulkan/pipeline/GraphicsPipeline.hpp"
#include "vma/vk_mem_alloc.h"
#include "Shader.hpp"

struct GLFWwindow;
namespace Candy::Graphics
{
    constexpr unsigned int FRAME_OVERLAP = 2;
  
    struct FrameData
    {
      VkSemaphore renderSemaphore=VK_NULL_HANDLE;
      VkSemaphore presentSemaphore=VK_NULL_HANDLE;
      VkFence renderFence=VK_NULL_HANDLE;
      CommandBuffer commandBuffer;
    };
    class GraphicsContext
    {
    
    private:
        GLFWwindow* handle;
        VkSurfaceKHR surface;
        SwapChain* swapChain;
        //UniquePtr<VulkanDeviceManager> deviceManager;
        UniquePtr<RenderPass> renderPass;
        uint32_t currentFrameIndex = 0;
        FrameData frames[FRAME_OVERLAP];

        /*VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        VkDescriptorSetLayout descriptorSetLayout;*/
        

        
        bool frameBufferResized=false;

        
        //std::vector<VkBuffer> uniformBuffers;
        //std::vector<VmaAllocation> uniformBufferAllocations;
        //std::vector<void*> uniformBuffersMapped;
        
        
    private:
        void CreateDescriptorPool();
        void CreateDescriptorSets();
        void CreateDescriptorSetLayout();
        void CreateUniformBuffers();
        void UpdateUniformBuffer(uint32_t currentImage);
        void InitSyncStructures();
        VkRenderPassBeginInfo BeginRenderPass();
        FrameData& GetCurrentFrame();
        

        
        
    public:
        explicit GraphicsContext(GLFWwindow* windowHandle);
        
    public:
        void SwapBuffers();
        void Terminate();
        void RebuildSwapChain();
        void OnFrameBufferResize();
        void UpdateFrameIndex();
        
        
        
    public:
        static UniquePtr<GraphicsContext> Create(GLFWwindow* windowHandle);
        
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