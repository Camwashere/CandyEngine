#include <candy/ui/UILayer.hpp>
#include <candy/app/Application.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>


namespace Candy
{
  using namespace Graphics;
  UILayer::UILayer()
  {
  
  }
  
  void UILayer::OnAttach()
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
    
    
    CANDY_CORE_ASSERT(vkCreateDescriptorPool(Vulkan::LogicalDevice(), &pool_info, nullptr, &uiPool)==VK_SUCCESS, "FAILED TO CREATE IMGUI DESCRIPTOR POOL!");
    
    
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;
    
    float fontSize = 18.0f;
    io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", fontSize);
    
    //this initializes imgui for glfw
    
    GLFWwindow* window = Application::GetMainWindowReference().handle;
    ImGui_ImplGlfw_InitForVulkan(window, true);
    //ImGui_ImplSDL2_InitForVulkan(_window);
    
    //this initializes imgui for Vulkan
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = Vulkan::Instance();
    init_info.PhysicalDevice = Vulkan::PhysicalDevice();
    init_info.Device = Vulkan::LogicalDevice();
    init_info.Queue = Vulkan::LogicalDevice().graphicsQueue;
    init_info.DescriptorPool = uiPool;
    init_info.MinImageCount = 3;
    init_info.ImageCount = 3;
    
    
    
    ImGui_ImplVulkan_Init(&init_info, Renderer::GetRenderPass());
    
    
    //execute a gpu command to upload imgui font textures
    RenderCommand::ImmediateSubmit([&](VkCommandBuffer cmd) {
    ImGui_ImplVulkan_CreateFontsTexture(cmd);
    });
    
  }
  
  void UILayer::OnDetach()
  {
    //clear font textures from cpu data
    ImGui_ImplVulkan_DestroyFontUploadObjects();
    ImGui_ImplVulkan_Shutdown();
    ImGui::DestroyContext();
    vkDestroyDescriptorPool(Vulkan::LogicalDevice(), uiPool, nullptr);
  }
  
  void UILayer::OnEvent(Events::Event &e)
  {
    Layer::OnEvent(e);
  }
  
  void UILayer::Begin()
  {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
  
  }
  
  void UILayer::End()
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)Application::GetMainWindowReference().GetWidth(), (float)Application::GetMainWindowReference().GetHeight());
    
    // Rendering
    ImGui::Render();
    
    
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), Vulkan::GetCurrentCommandBuffer());
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  
  }
}