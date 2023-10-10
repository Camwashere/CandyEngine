#include <candy/graphics/vulkan/VulkanDebugManager.hpp>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <GLFW/glfw3.h>
#include <candy/graphics/vulkan/VulkanPch.hpp>
const std::vector<const char*> validationLayers= {
        "VK_LAYER_KHRONOS_validation"
};


#ifdef CANDY_DEBUG
  #define CANDY_ENABLE_VALIDATION_LAYERS
#endif


namespace Candy::Graphics
{
  struct DebugManagerData
  {
    VkDebugUtilsMessengerEXT debugMessenger;
  };
  
  static DebugManagerData data;
    
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
      CANDY_PROFILE_FUNCTION();
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
    
    
    
    VkResult VulkanDebugManager::Init(VkInstance instance)
    {
      CANDY_PROFILE_FUNCTION();
      
      #ifdef CANDY_ENABLE_VALIDATION_LAYERS
        VkDebugUtilsMessengerCreateInfoEXT createInfo;
        PopulateDebugMessengerCreateInfo(createInfo);
      
        return CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &data.debugMessenger);
      #endif
      return VK_SUCCESS;
      
    }
    
    
    
    void VulkanDebugManager::Destroy()
    {
      CANDY_PROFILE_FUNCTION();
      #ifdef CANDY_ENABLE_VALIDATION_LAYERS
        DestroyDebugUtilsMessengerEXT(Vulkan::Instance(), data.debugMessenger, nullptr);
      #endif
      
    }
  
  std::vector<const char*> VulkanDebugManager::GetRequiredExtensions()
  {
    CANDY_PROFILE_FUNCTION();
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    #ifdef CANDY_ENABLE_VALIDATION_LAYERS
      extensions.push_back("VK_EXT_debug_utils");
    #endif
    
    return extensions;
  }
  
  std::vector<std::string> VulkanDebugManager::GetAvailableExtensions()
  {
    CANDY_PROFILE_FUNCTION();
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
    CANDY_PROFILE_FUNCTION();
    std::vector<std::string> extensions = GetAvailableExtensions();
    CANDY_CORE_INFO("Available Vulkan Extensions: ");
    for (const auto& extension : extensions)
    {
      CANDY_CORE_INFO("\t{0}", extension);
    }
  }
  
  VkInstanceCreateInfo VulkanDebugManager::GetInstanceCreateInfo()
  {
    CANDY_PROFILE_FUNCTION();
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
      #ifdef CANDY_ENABLE_VALIDATION_LAYERS
        return true;
      #else
      return false;
      #endif
      
    }
    
    bool VulkanDebugManager::ValidationLayersSupported()
    {
        return CheckValidationLayerSupport();
    }
    
    const std::vector<const char*>& VulkanDebugManager::GetValidationLayers(){return validationLayers;}
    std::uint32_t VulkanDebugManager::GetValidationLayerCount(){return validationLayers.size();}
    
    
}