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
#include "candy/graphics/shader/Shader.hpp"

/*void VulkanEngine::init_imgui()
{
  //1: create descriptor pool for IMGUI
  // the size of the pool is very oversize, but its copied from imgui demo itself.
  VkDescriptorPoolSize pool_sizes[] =
    {
      { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
      { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
      { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
      { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
    };
  
  VkDescriptorPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pool_info.maxSets = 1000;
  pool_info.poolSizeCount = 11;// std::size(pool_sizes);
  pool_info.pPoolSizes = pool_sizes;
  
  VkDescriptorPool imguiPool;
  VK_CHECK(vkCreateDescriptorPool(_device, &pool_info, nullptr, &imguiPool));
  
  
  // 2: initialize imgui library
  
  //this initializes the core structures of imgui
  ImGui::CreateContext();
  ImGui::GetIO().IniFilename = NULL;
  
  //this initializes imgui for SDL
  ImGui_ImplSDL2_InitForVulkan(_window);
  
  //this initializes imgui for Vulkan
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = _instance;
  init_info.PhysicalDevice = _chosenGPU;
  init_info.Device = _device;
  init_info.Queue = _graphicsQueue;
  init_info.DescriptorPool = imguiPool;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  
  ImGui_ImplVulkan_Init(&init_info, _renderPass);
  
  //execute a gpu command to upload imgui font textures
  immediate_submit([&](VkCommandBuffer cmd) {
  ImGui_ImplVulkan_CreateFontsTexture(cmd);
  });
  
  //clear font textures from cpu data
  ImGui_ImplVulkan_DestroyFontUploadObjects();
  
  //add the destroy the imgui created structures
  _mainDeletionQueue.push_function([=]() {
  
  vkDestroyDescriptorPool(_device, imguiPool, nullptr);
  ImGui_ImplVulkan_Shutdown();
  });
}*/
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
    };
    class GraphicsContext
    {
    
    private:
        GLFWwindow* handle;
        VkSurfaceKHR surface;
        SwapChain* swapChain;
        UniquePtr<RenderPass> renderPass;
        uint32_t currentFrameIndex = 0;
        FrameData frames[FRAME_OVERLAP];
        
        bool frameBufferResized=false;

        
    private:
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