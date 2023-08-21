#include <candy/graphics/vulkan/VulkanDebugManager.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <GLFW/glfw3.h>
const std::vector<const char*> validationLayers= {
        "VK_LAYER_KHRONOS_validation"
};


#ifdef CANDY_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif


namespace Candy::Graphics
{
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData)
    {
        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                CANDY_CORE_TRACE("VALIDATION LAYER TRACE: {0}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                CANDY_CORE_INFO("VALIDATION LAYER INFO: {0}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                CANDY_CORE_WARN("VALIDATION LAYER WARNING: {0}", pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                CANDY_CORE_ERROR("VALIDATION LAYER ERROR: {0}", pCallbackData->pMessage);
                break;
            default:
                break;
        }
        /*switch(messageType)
        {
          case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            CANDY_CORE_TRACE("VALIDATION LAYER GENERAL: {0}", pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            CANDY_CORE_TRACE("VALIDATION LAYER VALIDATION: {0}", pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            CANDY_CORE_TRACE("VALIDATION LAYER PERFORMANCE: {0}", pCallbackData->pMessage);
            break;
          case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
            CANDY_CORE_TRACE("VALIDATION LAYER DEVICE ADDRESS BINDING: {0}", pCallbackData->pMessage);
            break;
          default:
            break;
        }*/
        return VK_FALSE;
    }
    
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
    
    void VulkanDebugManager::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
    }
    
    bool static CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        for (const char* layerName : validationLayers)
        {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound)
            {
                return false;
            }
        }
        return true;
    }
    
    VulkanDebugManager::VulkanDebugManager(VkInstance instance)
    {
      if (enableValidationLayers)
      {
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        PopulateDebugMessengerCreateInfo(createInfo);
        
        CANDY_CORE_ASSERT(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) == VK_SUCCESS, "FAILED TO SET UP DEBUG MESSENGER!");
      }
      
    }
    
    VulkanDebugManager::~VulkanDebugManager()
    {
      if (enableValidationLayers)
      {
        DestroyDebugUtilsMessengerEXT(Vulkan::Instance(), debugMessenger, nullptr);
      }
    }
  
  std::vector<const char*> VulkanDebugManager::GetRequiredExtensions()
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
  
  std::vector<std::string> VulkanDebugManager::GetAvailableExtensions()
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
  
  void VulkanDebugManager::DisplayAvailableExtensions()
  {
    std::vector<std::string> extensions = GetAvailableExtensions();
    CANDY_CORE_INFO("Available Vulkan Extensions: ");
    for (const auto& extension : extensions)
    {
      CANDY_CORE_INFO("\t{0}", extension);
    }
  }
  
  VkInstanceCreateInfo VulkanDebugManager::GetInstanceCreateInfo()
  {
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    
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
    return createInfo;
  }
    
    
    
    bool VulkanDebugManager::ValidationLayersEnabled()
    {
        return enableValidationLayers;
    }
    
    bool VulkanDebugManager::ValidationLayersSupported()
    {
        return CheckValidationLayerSupport();
    }
    
    const std::vector<const char*>& VulkanDebugManager::GetValidationLayers(){return validationLayers;}
    std::uint32_t VulkanDebugManager::GetValidationLayerCount(){return validationLayers.size();}
    
    
}