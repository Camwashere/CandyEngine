#include <candy/graphics/vulkan/VulkanInstance.hpp>
#include <GLFW/glfw3.h>
#include <vma/vk_mem_alloc.h>

namespace Candy::Graphics
{
    //VulkanInstance* VulkanInstance::vulkanInstance=nullptr;
    
    VulkanInstance::VulkanInstance()
    {
      CANDY_CORE_ASSERT(VulkanDebugManager::ValidationLayersEnabled() && VulkanDebugManager::ValidationLayersSupported());
      VkApplicationInfo appInfo{};
      appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      appInfo.pApplicationName = "Hello Triangle";
      appInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 0);
      appInfo.pEngineName = "No Engine";
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
        createInfo.enabledLayerCount=0;
        createInfo.pNext = nullptr;
      }
      
      //VkInstanceCreateInfo createInfo = VulkanDebugManager::GetInstanceCreateInfo();
      //createInfo.pApplicationInfo = &appInfo;
      CANDY_CORE_ASSERT(vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS, "FAILED TO CREATE VULKAN INSTANCE!");
      
        
      debugManager = CreateUniquePtr<VulkanDebugManager>(instance);
    }
  
  VulkanInstance::~VulkanInstance()
  {
    vkDestroyInstance(instance, nullptr);
  }
    
    /*void VulkanInstance::CreateInstance()
    {
        CANDY_CORE_ASSERT(VulkanDebugManager::ValidationLayersEnabled() && VulkanDebugManager::ValidationLayersSupported());
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;
        
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        auto extensions = GetRequiredExtensions();
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
            createInfo.enabledLayerCount=0;
            createInfo.pNext = nullptr;
        }
        
        
        CANDY_CORE_ASSERT(vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS, "FAILED TO CREATE VULKAN INSTANCE!");
    }
    
    
    std::vector<const char*> VulkanInstance::GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if (VulkanDebugManager::ValidationLayersEnabled())
        {
            extensions.push_back("VK_EXT_debug_utils");
        }
        return extensions;
    }
    
    std::vector<std::string> VulkanInstance::GetAvailableExtensions()
    {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::vector<std::string> availableExtensions;
        for (auto extension : extensions)
        {
            availableExtensions.emplace_back(extension.extensionName);
        }
        return availableExtensions;
    }
    
    void VulkanInstance::DisplayAvailableExtensions()
    {
        std::vector<std::string> extensions = GetAvailableExtensions();
        CANDY_CORE_INFO("Available Vulkan Extensions: ");
        for (const auto& extension : extensions)
        {
            CANDY_CORE_INFO("\t{0}", extension);
        }
    }*/
    
    
    
    
}