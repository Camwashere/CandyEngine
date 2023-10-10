#pragma once

#include "CandyPch.hpp"
#include <vector>
#include <string>
#include "vulkan/VulkanDebugManager.hpp"
#include <candy/graphics/vulkan/SwapChain.hpp>
#include <candy/event/Events.hpp>
#include <candy/graphics/FrameResources.hpp>

struct GLFWwindow;
namespace Candy::Graphics
{
  
  struct FrameResources;
  
  
    class GraphicsContext
    {

    private:
        GLFWwindow* handle;
        VkSurfaceKHR surface=VK_NULL_HANDLE;
        UniquePtr<SwapChain> swapChain;
        uint32_t currentFrameIndex = 0;
        uint32_t previousFrameIndex=0;
        std::vector<FrameResources> frames;
        
        bool frameBufferResized=false;
        
        
    private:
        void InitSyncStructures();
        void CleanViewport();
        void CreateViewport();
        void RecreateViewport();
        void UpdateFrameIndex();
        
        void CreateDepthResources(uint32_t frameIndex, const Math::Vector2u& size);
    public:
        explicit GraphicsContext(GLFWwindow* window, VkSurfaceKHR windowSurface);
        
    public:
        void NextSwapChainImage();
        
        /**
         * @brief Submit the current batch of 'work' to the gpu.
         */
        void Submit();
        void Present();
        //void RebuildSwapChain(VkRenderPass renderPass);
        void OnFrameBufferResize(Events::FrameBufferResizeEvent& event);
        //void CleanSwapChain();
        SwapChain& GetSwapChain();
        VkSurfaceKHR GetSurface();
        VkSurfaceFormatKHR GetSurfaceFormat();
        
        
        [[nodiscard]] uint32_t GetCurrentFrameIndex()const;
        [[nodiscard]] uint32_t GetPreviousFrameIndex()const;
        
        FrameResources& GetCurrentFrame();
        FrameResources& GetFrame(uint32_t index);
        FrameResources& GetPreviousFrame();

        
        
    public:
      static bool IsDepthOnlyFormat(VkFormat format);
      static bool HasStencilComponent(VkFormat format);
      static VkFormat FindDepthFormat();
      static VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        
    private:
      friend class RenderCommand;
        friend class VulkanDebugManager;
        friend class VulkanDeviceManager;
        friend class VertexBuffer;
        friend class IndexBuffer;
        friend class SwapChain;
        friend class Renderer;
        friend class Vulkan;
        
    };
}