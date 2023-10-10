#include <candy/graphics/Vulkan.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define VMA_IMPLEMENTATION
#include <vma/vk_mem_alloc.h>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorLayoutCache.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/vulkan/DeletionQueue.hpp>

#include "candy/graphics/RenderCommand.hpp"
#include <candy/graphics/Renderer2D.hpp>
#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/texture/TextureManager.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
namespace Candy::Graphics
{
  static int MAX_FRAMES_IN_FLIGHT = 3;
  struct VulkanData
  {
    int currentFramesInFlight=2;
    VkInstance instance=nullptr;
    VulkanDeviceManager* deviceManager=nullptr;
    VmaAllocator allocator=nullptr;
    DescriptorAllocator* descriptorAllocator = nullptr;
    DescriptorLayoutCache descriptorLayoutCache;
    std::vector<SharedPtr<GraphicsContext>> contexts;
    GraphicsContext* currentContext = nullptr;
    DeletionQueue deletionQueue;
    std::filesystem::path vulkanFeaturesPath;
  };
  
  static VulkanData data;
  
  
  
  void Vulkan::InitDeviceManager(VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    data.deviceManager = new VulkanDeviceManager(surface);
    
    // Create allocators
    VmaAllocatorCreateInfo allocatorCreateInfo = {};
    
    allocatorCreateInfo.physicalDevice = data.deviceManager->physicalDevice;
    allocatorCreateInfo.device = data.deviceManager->logicalDevice;
    allocatorCreateInfo.instance = data.instance;
    
    CANDY_VULKAN_CHECK(vmaCreateAllocator(&allocatorCreateInfo, &data.allocator));
    
    data.descriptorAllocator = new DescriptorAllocator();
    Vulkan::DeletionQueue().Push(data.descriptorAllocator);
    
    
  }
  
  void Vulkan::InitInstance(const std::string& appName, const Version& appVersion)
  {
    CANDY_CORE_ASSERT(VulkanDebugManager::ValidationLayersEnabled() && VulkanDebugManager::ValidationLayersSupported());
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(appVersion.GetMajor(), appVersion.GetMinor(), appVersion.GetPatch());
    appInfo.pEngineName = "Candy Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;
    
    
    //VkInstanceCreateInfo createInfo = VulkanDebugManager::GetInstanceCreateInfo();
    
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    auto extensions = VulkanDebugManager::GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    
    // TODO Figure out how to move this section to VulkanDebugManager
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (VulkanDebugManager::ValidationLayersEnabled())
    {
      createInfo.enabledLayerCount = static_cast<uint32_t>(VulkanDebugManager::GetValidationLayerCount());
      createInfo.ppEnabledLayerNames = VulkanDebugManager::GetValidationLayers().data();
      
      VulkanDebugManager::PopulateDebugMessengerCreateInfo(debugCreateInfo);
      createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    }
    else
    {
      createInfo.enabledLayerCount = 0;
      createInfo.pNext = nullptr;
    }
    
    
    CANDY_VULKAN_CHECK(vkCreateInstance(&createInfo, nullptr, &data.instance));
  }
  
  
  GraphicsContext* Vulkan::Init(GLFWwindow* mainWindow)
  {
    CANDY_PROFILE_FUNCTION();
    data.vulkanFeaturesPath = "config/vulkan/enabledVulkanFeatures.csv";
    data.deviceManager = nullptr;
    data.deletionQueue.Push(&data.descriptorLayoutCache);
    InitInstance("Candy App", Version(1, 0, 0));
    VulkanDebugManager::Init(data.instance);
    VkSurfaceKHR surface;
    CANDY_VULKAN_CHECK(glfwCreateWindowSurface(Vulkan::Instance(), mainWindow, nullptr, &surface));
    Vulkan::DeletionQueue().Push(surface);
    
    Vulkan::InitDeviceManager(surface);
    Renderer::Init(Vulkan::GetSurfaceFormat(surface));
    RenderCommand::Init(surface);
    
    data.contexts.push_back(CreateSharedPtr<GraphicsContext>(mainWindow, surface));
    data.currentContext = data.contexts[0].get();
    Renderer::SetTarget(data.currentContext);
    RenderCommand::SetTarget(data.currentContext);
    
    TextureManager::Init();
    ShaderLibrarySettings settings = ShaderLibrarySettings::Load("config/shader/librarySettings.yml");
    
    bool shaderLibraryInitialized = ShaderLibrary::Init(settings);
    CANDY_CORE_ASSERT(shaderLibraryInitialized, "Failed to initialize shader library");
    Renderer2D::Init();
    Renderer3D::Init();
    
    return data.currentContext;
    
  }

 DeletionQueue& Vulkan::DeletionQueue()
 {
   
   return data.deletionQueue;
 }
  VkInstance Vulkan::Instance()
  {
    return data.instance;
  }
  
  VmaAllocator Vulkan::Allocator()
  {
    return data.allocator;
  }
  
  PhysicalDevice& Vulkan::PhysicalDevice()
  {
    return data.deviceManager->physicalDevice;
  }
  LogicalDevice& Vulkan::LogicalDevice()
  {
    return data.deviceManager->logicalDevice;
  }
  
  bool Vulkan::HasDeviceManager()
  {
    return data.deviceManager != nullptr;
  }
  const std::filesystem::path& Vulkan::GetVulkanFeaturesPath()
  {
   return data.vulkanFeaturesPath;
  }
  DescriptorAllocator& Vulkan::GetDescriptorAllocator()
  {
    return *data.descriptorAllocator;
  }
  DescriptorLayoutCache& Vulkan::GetDescriptorLayoutCache()
  {
    return data.descriptorLayoutCache;
  }
  VkSurfaceFormatKHR Vulkan::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
  {
    CANDY_PROFILE_FUNCTION();
    for (const auto& availableFormat : availableFormats)
    {
      if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        return availableFormat;
      }
    }
    return availableFormats[0];
  }
  
  VkSurfaceFormatKHR Vulkan::GetSurfaceFormat(VkSurfaceKHR surface)
  {
    SwapChainSupportDetails swapChainSupport = Vulkan::PhysicalDevice().QuerySwapChainSupport(surface);
    return ChooseSwapSurfaceFormat(swapChainSupport.formats);
  }
  

  

  GraphicsContext& Vulkan::GetCurrentContext()
  {
    CANDY_CORE_ASSERT(data.currentContext, "FAILED TO GET CURRENT CONTEXT. THE CURRENT CONTEXT IS NULL");
    return *data.currentContext;
  }
  
  float Vulkan::GetContextSizeRatio()
  {
    return (float)GetCurrentContext().swapChain->extent.width / (float)GetCurrentContext().swapChain->extent.height;
  }
  
  int Vulkan::GetFramesInFlight()
  {
    return data.currentFramesInFlight;
  }

  void Vulkan::Shutdown()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_VULKAN_CHECK(vkDeviceWaitIdle(LogicalDevice()));
    data.deletionQueue.Flush();
    
    
    VulkanDebugManager::Destroy();
    vkDestroyInstance(Instance(), nullptr);
   
  }
}