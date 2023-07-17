#include <candy/graphics/GraphicsContext.hpp>
#include <CandyPch.hpp>
#include <GLFW/glfw3.h>
#include <set>
#include <candy/graphics/vulkan/VulkanBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
    
    
    struct Vertex {
        Math::Vector2 pos;
        Math::Vector3 color;
        
        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            
            return bindingDescription;
        }
        
        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
            
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);
            
            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);
            
            return attributeDescriptions;
        }
    };
    const std::vector<Vertex> vertices1 = {
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
            {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };
    
    const std::vector<Math::Vector2> vertices = {
            {-0.5f, -0.5f},
            {0.5f, -0.5f},
            {0.5f, 0.5f},
            {-0.5f, 0.5f}
    };
    
    const std::vector<Math::Vector3> colors = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {1.0f, 1.0f, 1.0f}
    };
    
    const std::vector<uint32_t> indices = {
            0, 1, 2, 2, 3, 0
    };
    
    
    
    
        
    GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
    {
      CANDY_CORE_INFO("GRAPHICS CONTEXT CONSTRUCTOR");
      if (windowHandle == nullptr)
      {
        CANDY_CORE_INFO("NULL WINDOW HANDLE!");
      }
      CANDY_CORE_INFO("WAA");
      handle = windowHandle;
      CANDY_CORE_ASSERT(glfwCreateWindowSurface(Vulkan::Instance(), windowHandle, nullptr, &surface) == VK_SUCCESS, "Failed to create vulkan window surface!");
      Vulkan::InitDeviceManager(surface);
      
      //deviceManager = CreateUniquePtr<VulkanDeviceManager>(surface);
      CANDY_CORE_INFO("CREATED DEVICE MANAGER");
      swapChain = new SwapChain(this);
      CANDY_CORE_INFO("CREATED SWAPCHAIN");
      renderPass = CreateUniquePtr<RenderPass>(swapChain->imageFormat);
      CANDY_CORE_INFO("CREATED RENDER PASS");
      swapChain->CreateFrameBuffers(*renderPass);
      CANDY_CORE_INFO("CREATED FRAME BUFFERS");
      InitSyncStructures();
      CANDY_CORE_INFO("INIT SYNC STRUCTURES");
        //Init();
    }
  void GraphicsContext::InitSyncStructures()
  {
    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    
    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    
    for (int i = 0; i < FRAME_OVERLAP; i++) {
      frames[i].commandBuffer.Init(surface);
      CANDY_CORE_ASSERT(vkCreateFence(Vulkan::LogicalDevice(), &fenceCreateInfo, nullptr, &frames[i].renderFence)==VK_SUCCESS);
      CANDY_CORE_ASSERT(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].presentSemaphore)==VK_SUCCESS);
      CANDY_CORE_ASSERT(vkCreateSemaphore(Vulkan::LogicalDevice(), &semaphoreCreateInfo, nullptr, &frames[i].renderSemaphore)==VK_SUCCESS);
    }
  }
  
  VkRenderPassBeginInfo GraphicsContext::BeginRenderPass()
  {
      return renderPass->BeginPass(swapChain->GetCurrentFrameBuffer(), swapChain->extent);
  }

    void GraphicsContext::CreateDescriptorPool()
    {
        /*VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        
        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        
        poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        
        CANDY_CORE_ASSERT(vkCreateDescriptorPool(Vulkan::LogicalDevice, &poolInfo, nullptr, &descriptorPool) == VK_SUCCESS, "Failed to create descriptor pooL!");*/
        
    }
    
    void GraphicsContext::CreateDescriptorSets()
    {
        /*std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();
        
        
        
        descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
        CANDY_CORE_ASSERT(vkAllocateDescriptorSets(Vulkan::LogicalDevice, &allocInfo, descriptorSets.data()) == VK_SUCCESS, "Failed to allocate descriptor sets!");
        
        for (size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++)
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);
            
            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            
            
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            
            descriptorWrite.pBufferInfo = &bufferInfo;
            descriptorWrite.pImageInfo = nullptr; // Optional
            descriptorWrite.pTexelBufferView = nullptr; // Optional
            
            vkUpdateDescriptorSets(Vulkan::LogicalDevice, 1, &descriptorWrite, 0, nullptr);
        }*/
        
        
    }
    void GraphicsContext::CreateDescriptorSetLayout()
    {
        /*VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.descriptorCount = 1;
        
        // Only referencing descriptor from the vertex shader
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
        
        uboLayoutBinding.pImmutableSamplers = nullptr; // Optional
        
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;
        
        CANDY_CORE_ASSERT(vkCreateDescriptorSetLayout(Vulkan::LogicalDevice, &layoutInfo, nullptr, &descriptorSetLayout) == VK_SUCCESS, "Failed to create descriptor set layout!");*/
    
    }
    
    void GraphicsContext::CreateUniformBuffers()
    {
        /*VkDeviceSize bufferSize = sizeof(UniformBufferObject);
        
        uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        uniformBufferAllocations.resize(MAX_FRAMES_IN_FLIGHT);
        uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);
        
        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            VulkanBuffer::CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], &uniformBufferAllocations[i]);
            
            vmaMapMemory(Vulkan::Allocator(), uniformBufferAllocations[i], &uniformBuffersMapped[i]);
        }*/
        
    }
    
    void GraphicsContext::UpdateUniformBuffer(uint32_t currentImage)
    {
        static auto startTime = std::chrono::high_resolution_clock::now();
        
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
        
        UniformBufferObject ubo{};
        
        ubo.model = Matrix4::Rotate(Matrix4::IDENTITY, time * Math::ToRadians(90.0f), Math::Vector3(0.0f, 0.0f, 1.0f));
        ubo.view = Matrix4::LookAt(Vector3(2.0f, 2.0f, 2.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
        ubo.proj = Matrix4::Perspective(Math::ToRadians(45.0f), (float)swapChain->extent.width / (float) swapChain->extent.height, 0.1f, 10.0f);
        
        ubo.proj[1,1] *= -1;
        
        //ubo.model = Matrix4::Transpose(ubo.model);
        //ubo.view = Matrix4::Transpose(ubo.view);
        //ubo.proj = Matrix4::Transpose(ubo.proj);
        
        //memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
        
    }
  
  
  FrameData& GraphicsContext::GetCurrentFrame(){return frames[currentFrameIndex];}
  


    
    

  
  
    void GraphicsContext::SwapBuffers()
    {
      CANDY_PROFILE_FUNCTION();
      CANDY_CORE_ASSERT(vkWaitForFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence, true, UINT64_MAX) == VK_SUCCESS);
      
      VkResult result = swapChain->AcquireNextImage(GetCurrentFrame().presentSemaphore, UINT64_MAX);
      
      if (result == VK_ERROR_OUT_OF_DATE_KHR)
      {
        frameBufferResized = false;
        swapChain->Rebuild(*renderPass);
      }
      else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
      {
        CANDY_CORE_ASSERT(false, "Failed to acquire swap chain image!");
      }
      
      
      
      CANDY_CORE_ASSERT(vkResetFences(Vulkan::LogicalDevice(), 1, &GetCurrentFrame().renderFence) == VK_SUCCESS);
      
      
    }
    
    void GraphicsContext::RebuildSwapChain()
    {
      swapChain->Rebuild(*renderPass);
    }
    
    void GraphicsContext::Terminate()
    {
        vkDeviceWaitIdle(Vulkan::LogicalDevice());
        //swapChain->Clean();
        
        /*for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
        {
          vmaUnmapMemory(VulkanInstance::Allocator(), uniformBufferAllocations[i]);
          VulkanBuffer::DestroyBuffer(uniformBuffers[i], uniformBufferAllocations[i]);
        }
        vkDestroyDescriptorPool(Vulkan::LogicalDevice, descriptorPool, nullptr);
        vkDestroyDescriptorSetLayout(Vulkan::LogicalDevice, descriptorSetLayout, nullptr);
        vertexArray->Clear();
        
        //vkDestroyPipeline(Vulkan::LogicalDevice, graphicsPipeline, nullptr);
        //vkDestroyPipelineLayout(Vulkan::LogicalDevice, pipelineLayout, nullptr);
        graphicsPipeline.Destroy();
        delete renderPass;
        for (size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++)
        {
            vkDestroySemaphore(Vulkan::LogicalDevice, imageAvailableSemaphores[i], nullptr);
            vkDestroySemaphore(Vulkan::LogicalDevice, renderFinishedSemaphores[i], nullptr);
            vkDestroyFence(Vulkan::LogicalDevice, inFlightFences[i], nullptr);
        }
      
        
        delete commandBuffer;*/
      renderPass->Destroy();
      for (size_t i=0; i<FRAME_OVERLAP; i++)
      {
        
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].renderSemaphore, nullptr);
        vkDestroySemaphore(Vulkan::LogicalDevice(), frames[i].presentSemaphore, nullptr);
        vkDestroyFence(Vulkan::LogicalDevice(), frames[i].renderFence, nullptr);
      }
      
      for (size_t i=0; i<FRAME_OVERLAP; i++)
      {
        frames[i].commandBuffer.Destroy();
      }
        
        vkDestroySurfaceKHR(Vulkan::Instance(), surface, nullptr);
        
        //vkDestroyDevice(Vulkan::LogicalDevice, nullptr);
        //VulkanInstance::Shutdown();
        //vkDestroyInstance(VulkanInstance::Get(), nullptr);
    }
  
  void GraphicsContext::OnFrameBufferResize()
  {
      frameBufferResized = true;
  }
  
  void GraphicsContext::UpdateFrameIndex()
  {
    currentFrameIndex = (currentFrameIndex + 1) % FRAME_OVERLAP;
  }
    
}