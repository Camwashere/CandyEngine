#include <candy/ui/UILayer.hpp>
#include <candy/app/Application.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/vulkan/RenderPass.hpp>
#include <imguizmo/ImGuizmo.h>
#include <CandyEngine.hpp>
#include <candy/project/ProjectManager.hpp>
namespace Candy
{
  using namespace Graphics;
  UILayer::UILayer()
  {
  
  }
  
  void UILayer::OnAttach()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_INFO("IMGui Version: {}", ImGui::GetVersion());
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
    
    
    
    CANDY_VULKAN_CHECK(vkCreateDescriptorPool(Vulkan::LogicalDevice(), &pool_info, nullptr, &uiPool));
    
    
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
    std::filesystem::path projectConfigPath = ProjectManager::GetConfigDirectory() / "ui/imgui.ini";
    iniPath = projectConfigPath.string();
    io.IniFilename = iniPath.c_str();
    io.IniSavingRate = 5.0f;
    
    float fontSize = 18.0f;
    io.Fonts->AddFontFromFileTTF(std::filesystem::path(CandyEngine::GetInternalAssetsDirectory() / "fonts/opensans/OpenSans-Bold.ttf").string().c_str(), fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF(std::filesystem::path(CandyEngine::GetInternalAssetsDirectory() / "fonts/opensans/OpenSans-Regular.ttf").string().c_str(), fontSize);
    
    //this initializes imgui for glfw
    
    GLFWwindow* window = Application::GetMainWindowReference().handle;
    ImGui_ImplGlfw_InitForVulkan(window, true);
    
    //this initializes imgui for Vulkan
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = Vulkan::Instance();
    init_info.PhysicalDevice = Vulkan::PhysicalDevice();
    init_info.Device = Vulkan::LogicalDevice();
    init_info.Queue = Vulkan::LogicalDevice().graphicsQueue;
    init_info.DescriptorPool = uiPool;
    init_info.MinImageCount = 3;
    init_info.ImageCount = 10;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    VK_SAMPLE_COUNT_16_BIT;
    
   
    
    
    
    
    
    ImGui_ImplVulkan_Init(&init_info, Renderer::GetUIPass());
    
    
    //execute a gpu command to upload imgui font textures
    RenderCommand::ImmediateSubmit([&](VkCommandBuffer cmd) {
    ImGui_ImplVulkan_CreateFontsTexture(cmd);
    });
    
    // Clear font texture from cpu memory
    ImGui_ImplVulkan_DestroyFontUploadObjects();
    RenderTarget& viewportTarget = Renderer::GetViewportTarget();
    ImageResource& viewportResource = viewportTarget.imageResources[0];
    ImageResource& depthResource = viewportTarget.imageResources[1];
    for (int i=0; i<Vulkan::GetFramesInFlight(); i++)
    {
      Renderer::GetFrame(i).viewportDescriptor = ImGui_ImplVulkan_AddTexture(viewportResource.imageView.GetSampler(), viewportResource.imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      //Renderer::GetFrame(i).viewportData.viewportDepthDescriptor = ImGui_ImplVulkan_AddTexture(depthResource.imageView.GetSampler(), depthResource.imageView, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }
    
  }
  
  void UILayer::OnDetach()
  {
    CANDY_PROFILE_FUNCTION();
    vkDeviceWaitIdle(Vulkan::LogicalDevice());
    
    vkDestroyDescriptorPool(Vulkan::LogicalDevice(), uiPool, nullptr);
    ImGui_ImplVulkan_Shutdown();
  }
  
  void UILayer::OnEvent(Events::Event &e)
  {
    CANDY_PROFILE_FUNCTION();
    if (blockEvents)
    {
      ImGuiIO& io = ImGui::GetIO();
      e.SetHandled(e.IsHandled() | (e.GetClass()==Events::EventClass::MOUSE) & io.WantCaptureMouse);
      e.SetHandled(e.IsHandled() | (e.GetClass()==Events::EventClass::KEYBOARD) & io.WantCaptureKeyboard);
    }
  }
  void UILayer::BlockEvents(bool block)
  {
    blockEvents = block;
  }
  void UILayer::Begin()
  {
    CANDY_PROFILE_FUNCTION();
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
    Renderer::BeginEditorChain();
    //Renderer::BeginGumPass();
    
  
  }
  
  void UILayer::End()
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)Application::GetMainWindowReference().GetWidth(), (float)Application::GetMainWindowReference().GetHeight());
    
    // Rendering
    ImGui::Render();
    
    
    
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), RenderCommand::GetRenderCommandBuffer());
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  
  }
}