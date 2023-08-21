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
#include "StorageBuffer.hpp"
#include <candy/event/Events.hpp>
#include <candy/graphics/PixelBuffer.hpp>

struct GLFWwindow;
namespace Candy::Graphics
{
    static constexpr unsigned int FRAME_OVERLAP = 2;
    static constexpr unsigned int MAX_OBJECTS = 100;
    static constexpr int GLOBAL_SET=0;
    static constexpr int OBJECT_SET=1;
    static constexpr int MATERIAL_SET=2;
  
    struct ViewportFrameData
    {
      VkDescriptorSet viewportDescriptor=VK_NULL_HANDLE;
      VkDescriptorSet viewportDepthDescriptor=VK_NULL_HANDLE;
      //VkDescriptorSet viewportSelectionDescriptor=VK_NULL_HANDLE;
      Image viewportImage;
      Image selectionImage;
      Image depthImage;
      ImageView viewportImageView;
      ImageView selectionImageView;
      ImageView depthImageView;
      FrameBuffer viewportFrameBuffer;
      FrameBuffer selectionFrameBuffer;
      PixelBuffer* selectionPixelBuffer;
      
    };
    struct FrameData
    {
      VkSemaphore renderSemaphore=VK_NULL_HANDLE;
      VkSemaphore presentSemaphore=VK_NULL_HANDLE;
      VkFence renderFence=VK_NULL_HANDLE;
      CommandBuffer commandBuffer;
      std::array<VkDescriptorSet, 3> descriptorSets;
      
      ViewportFrameData viewportData;
      SharedPtr<UniformBuffer> uniformBuffer;
      SharedPtr<StorageBuffer> storageBuffer;
      SharedPtr<UniformBuffer> materialBuffer;
      
      
      
      
      VkDescriptorSet& GlobalDescriptor(){return descriptorSets[GLOBAL_SET];}
      VkDescriptorSet& ObjectDescriptor(){return descriptorSets[OBJECT_SET];}
      VkDescriptorSet& MaterialDescriptor(){return descriptorSets[MATERIAL_SET];}
      //VkDescriptorSet& GumDescriptor(){return gumDescriptor;}
      VkDescriptorSet& GetDescriptorSet(uint32_t index){return descriptorSets[index];}
      [[nodiscard]] VkDescriptorSet GlobalDescriptor()const{return descriptorSets[GLOBAL_SET];}
      [[nodiscard]] VkDescriptorSet ObjectDescriptor()const{return descriptorSets[OBJECT_SET];}
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
        void CleanViewport();
        void CreateViewport();
        void RecreateViewport();
        //VkRenderPassBeginInfo BeginRenderPass();
        void UpdateFrameIndex();
        
        //void RecreateTarget(const Math::Vector2u& size);
        void CreateDepthResources(uint32_t frameIndex, const Math::Vector2u& size);
    public:
        explicit GraphicsContext(GLFWwindow* windowHandle);
        
    public:
      //void RecreateTarget();
        void SwapBuffers();
        void Present();
        //VkDescriptorSet GumDescriptor();
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
        //FrameBuffer& GetTargetFrameBuffer();
        //ImageView& GetTargetImageView(){return targetView;}
        //Image& GetTargetImage(){return targetImage;}
        
        
    public:
      static UniquePtr<GraphicsContext> Create(GLFWwindow* windowHandle);
      static bool IsDepthOnlyFormat(VkFormat format);
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