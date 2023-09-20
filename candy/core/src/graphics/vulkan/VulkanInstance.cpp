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
      CANDY_VULKAN_CHECK(vkCreateInstance(&createInfo, nullptr, &instance));
      
        
      debugManager = CreateUniquePtr<VulkanDebugManager>(instance);
    }
  
  VulkanInstance::~VulkanInstance()
  {
    vkDestroyInstance(instance, nullptr);
  }

    
    
    
    
}