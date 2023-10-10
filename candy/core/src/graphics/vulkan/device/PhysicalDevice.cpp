#include <candy/graphics/vulkan/device/PhysicalDevice.hpp>
#include <set>
#include <candy/graphics/vulkan/device/VulkanDeviceManager.hpp>
#include <string>
#include <CandyPch.hpp>
#include <candy/graphics/Vulkan.hpp>
namespace Candy::Graphics
{
  static std::unordered_map<std::string, VkBool32> featureMap;
  
  
  static std::unordered_map<std::string, VkBool32> additionalFeatureMap{{"shaderDrawParameters", VK_FALSE}};
  
  
  bool PhysicalDevice::EnableDeviceFeature(const std::string& name)
  {
    auto it = featureMap.find(name);
    if (it != featureMap.end())
    {
      it->second = VK_TRUE;
      CANDY_CORE_INFO("Enabled device feature {0}", name);
      return true;
    }
    
    CANDY_CORE_WARN("Failed to enable device feature {0}, name not found!", name);
    return false;
  }
  bool PhysicalDevice::EnableDeviceFeatures(const std::vector<std::string>& names)
  {
    bool success = true;
    for (const auto& name : names)
    {
      success &= EnableDeviceFeature(name);
    }
    return success;
  }
  bool PhysicalDevice::CheckSupportedDeviceFeatures(const VkPhysicalDeviceFeatures2& features)
  {
    bool success = true;
    
    // Base features check
    success |= (features.features.alphaToOne == featureMap["alphaToOne"]);
    success |= (features.features.depthBiasClamp == featureMap["depthBiasClamp"]);
    success |= (features.features.depthBounds == featureMap["depthBounds"]);
    success |= (features.features.depthClamp == featureMap["depthClamp"]);
    success |= (features.features.dualSrcBlend == featureMap["dualSrcBlend"]);
    success |= (features.features.fillModeNonSolid == featureMap["fillModeNonSolid"]);
    success |= (features.features.fragmentStoresAndAtomics == featureMap["fragmentStoresAndAtomics"]);
    success |= (features.features.fullDrawIndexUint32 == featureMap["fullDrawIndexUint32"]);
    success |= (features.features.geometryShader == featureMap["geometryShader"]);
    success |= (features.features.imageCubeArray == featureMap["imageCubeArray"]);
    success |= (features.features.independentBlend == featureMap["independentBlend"]);
    success |= (features.features.logicOp == featureMap["logicOp"]);
    success |= (features.features.multiDrawIndirect == featureMap["multiDrawIndirect"]);
    success |= (features.features.multiViewport == featureMap["multiViewport"]);
    success |= (features.features.occlusionQueryPrecise == featureMap["occlusionQueryPrecise"]);
    success |= (features.features.pipelineStatisticsQuery == featureMap["pipelineStatisticsQuery"]);
    success |= (features.features.robustBufferAccess == featureMap["robustBufferAccess"]);
    success |= (features.features.samplerAnisotropy == featureMap["samplerAnisotropy"]);
    success |= (features.features.sampleRateShading == featureMap["sampleRateShading"]);
    success |= (features.features.shaderClipDistance == featureMap["shaderClipDistance"]);
    success |= (features.features.shaderCullDistance == featureMap["shaderCullDistance"]);
    success |= (features.features.shaderFloat64 == featureMap["shaderFloat64"]);
    success |= (features.features.shaderImageGatherExtended == featureMap["shaderImageGatherExtended"]);
    success |= (features.features.shaderInt16 == featureMap["shaderInt16"]);
    success |= (features.features.shaderInt64 == featureMap["shaderInt64"]);
    success |= (features.features.shaderResourceMinLod == featureMap["shaderResourceMinLod"]);
    success |= (features.features.shaderResourceResidency == featureMap["shaderResourceResidency"]);
    success |= (features.features.shaderSampledImageArrayDynamicIndexing == featureMap["shaderSampledImageArrayDynamicIndexing"]);
    success |= (features.features.shaderStorageBufferArrayDynamicIndexing == featureMap["shaderStorageBufferArrayDynamicIndexing"]);
    success |= (features.features.shaderStorageImageArrayDynamicIndexing == featureMap["shaderStorageImageArrayDynamicIndexing"]);
    success |= (features.features.shaderStorageImageExtendedFormats == featureMap["shaderStorageImageExtendedFormats"]);
    success |= (features.features.shaderStorageImageMultisample == featureMap["shaderStorageImageMultisample"]);
    success |= (features.features.shaderStorageImageReadWithoutFormat == featureMap["shaderStorageImageReadWithoutFormat"]);
    success |= (features.features.shaderStorageImageWriteWithoutFormat == featureMap["shaderStorageImageWriteWithoutFormat"]);
    success |= (features.features.shaderTessellationAndGeometryPointSize == featureMap["shaderTessellationAndGeometryPointSize"]);
    success |= (features.features.shaderUniformBufferArrayDynamicIndexing == featureMap["shaderUniformBufferArrayDynamicIndexing"]);
    success |= (features.features.sparseBinding == featureMap["sparseBinding"]);
    success |= (features.features.sparseResidency16Samples == featureMap["sparseResidency16Samples"]);
    success |= (features.features.sparseResidency2Samples == featureMap["sparseResidency2Samples"]);
    success |= (features.features.sparseResidency4Samples == featureMap["sparseResidency4Samples"]);
    success |= (features.features.sparseResidency8Samples == featureMap["sparseResidency8Samples"]);
    success |= (features.features.sparseResidencyAliased == featureMap["sparseResidencyAliased"]);
    success |= (features.features.sparseResidencyBuffer == featureMap["sparseResidencyBuffer"]);
    success |= (features.features.sparseResidencyImage2D == featureMap["sparseResidencyImage2D"]);
    success |= (features.features.sparseResidencyImage3D == featureMap["sparseResidencyImage3D"]);
    success |= (features.features.tessellationShader == featureMap["tessellationShader"]);
    success |= (features.features.textureCompressionASTC_LDR == featureMap["textureCompressionASTC_LDR"]);
    success |= (features.features.textureCompressionBC == featureMap["textureCompressionBC"]);
    success |= (features.features.textureCompressionETC2 == featureMap["textureCompressionETC2"]);
    success |= (features.features.variableMultisampleRate == featureMap["variableMultisampleRate"]);
    success |= (features.features.vertexPipelineStoresAndAtomics == featureMap["vertexPipelineStoresAndAtomics"]);
    success |= (features.features.wideLines == featureMap["wideLines"]);
    success |= (features.features.inheritedQueries == featureMap["inheritedQueries"]);
    success |= (features.features.drawIndirectFirstInstance == featureMap["drawIndirectFirstInstance"]);
    
    
    return success;

    
  }
  
  VkPhysicalDeviceFeatures2 PhysicalDevice::GetSupportedDeviceFeatures()
  {
    VkPhysicalDeviceFeatures2 features{};
    // Base features check
    features.features.alphaToOne = featureMap["alphaToOne"];
    features.features.depthBiasClamp = featureMap["depthBiasClamp"];
    features.features.depthBounds = featureMap["depthBounds"];
    features.features.depthClamp = featureMap["depthClamp"];
    features.features.dualSrcBlend = featureMap["dualSrcBlend"];
    features.features.fillModeNonSolid = featureMap["fillModeNonSolid"];
    features.features.fragmentStoresAndAtomics = featureMap["fragmentStoresAndAtomics"];
    features.features.fullDrawIndexUint32 = featureMap["fullDrawIndexUint32"];
    features.features.geometryShader = featureMap["geometryShader"];
    features.features.imageCubeArray = featureMap["imageCubeArray"];
    features.features.independentBlend = featureMap["independentBlend"];
    features.features.logicOp = featureMap["logicOp"];
    features.features.multiDrawIndirect = featureMap["multiDrawIndirect"];
    features.features.multiViewport = featureMap["multiViewport"];
    features.features.occlusionQueryPrecise = featureMap["occlusionQueryPrecise"];
    features.features.pipelineStatisticsQuery = featureMap["pipelineStatisticsQuery"];
    features.features.robustBufferAccess = featureMap["robustBufferAccess"];
    features.features.samplerAnisotropy = featureMap["samplerAnisotropy"];
    features.features.sampleRateShading = featureMap["sampleRateShading"];
    features.features.shaderClipDistance = featureMap["shaderClipDistance"];
    features.features.shaderCullDistance = featureMap["shaderCullDistance"];
    features.features.shaderFloat64 = featureMap["shaderFloat64"];
    features.features.shaderImageGatherExtended = featureMap["shaderImageGatherExtended"];
    features.features.shaderInt16 = featureMap["shaderInt16"];
    features.features.shaderInt64 = featureMap["shaderInt64"];
    features.features.shaderResourceMinLod = featureMap["shaderResourceMinLod"];
    features.features.shaderResourceResidency = featureMap["shaderResourceResidency"];
    features.features.shaderSampledImageArrayDynamicIndexing = featureMap["shaderSampledImageArrayDynamicIndexing"];
    features.features.shaderStorageBufferArrayDynamicIndexing = featureMap["shaderStorageBufferArrayDynamicIndexing"];
    features.features.shaderStorageImageArrayDynamicIndexing = featureMap["shaderStorageImageArrayDynamicIndexing"];
    features.features.shaderStorageImageExtendedFormats = featureMap["shaderStorageImageExtendedFormats"];
    features.features.shaderStorageImageMultisample = featureMap["shaderStorageImageMultisample"];
    features.features.shaderStorageImageReadWithoutFormat = featureMap["shaderStorageImageReadWithoutFormat"];
    features.features.shaderStorageImageWriteWithoutFormat = featureMap["shaderStorageImageWriteWithoutFormat"];
    features.features.shaderTessellationAndGeometryPointSize = featureMap["shaderTessellationAndGeometryPointSize"];
    features.features.shaderUniformBufferArrayDynamicIndexing = featureMap["shaderUniformBufferArrayDynamicIndexing"];
    features.features.sparseBinding = featureMap["sparseBinding"];
    features.features.sparseResidency16Samples = featureMap["sparseResidency16Samples"];
    features.features.sparseResidency2Samples = featureMap["sparseResidency2Samples"];
    features.features.sparseResidency4Samples = featureMap["sparseResidency4Samples"];
    features.features.sparseResidency8Samples = featureMap["sparseResidency8Samples"];
    features.features.sparseResidencyAliased = featureMap["sparseResidencyAliased"];
    features.features.sparseResidencyBuffer = featureMap["sparseResidencyBuffer"];
    features.features.sparseResidencyImage2D = featureMap["sparseResidencyImage2D"];
    features.features.sparseResidencyImage3D = featureMap["sparseResidencyImage3D"];
    features.features.tessellationShader = featureMap["tessellationShader"];
    features.features.textureCompressionASTC_LDR = featureMap["textureCompressionASTC_LDR"];
    features.features.textureCompressionBC = featureMap["textureCompressionBC"];
    features.features.textureCompressionETC2 = featureMap["textureCompressionETC2"];
    features.features.variableMultisampleRate = featureMap["variableMultisampleRate"];
    features.features.vertexPipelineStoresAndAtomics = featureMap["vertexPipelineStoresAndAtomics"];
    features.features.wideLines = featureMap["wideLines"];
    features.features.inheritedQueries = featureMap["inheritedQueries"];
    features.features.drawIndirectFirstInstance = featureMap["drawIndirectFirstInstance"];
    
    return features;
  }
  struct ScoredDevice
  {
    long long int score;
    VkPhysicalDevice device;
  };
  static std::vector<ScoredDevice> RankSuitableDevices(VkSurfaceKHR surface, const std::vector<VkPhysicalDevice>& foundDevices)
  {
    CANDY_PROFILE_FUNCTION();
    std::vector<ScoredDevice> scoredDevices;
    for (auto d : foundDevices)
    {
      ScoredDevice sd{PhysicalDevice::RateDeviceSuitability(d, surface), d};
      
      if (sd.score > 0)
      {
        scoredDevices.push_back(sd);
      }
    }
    
    std::sort(scoredDevices.begin(), scoredDevices.end(), [](const ScoredDevice& a, const ScoredDevice& b){return a.score > b.score;});
    
    return scoredDevices;
  }
  
  
  static void InitFeatures()
  {
    
    std::ifstream file(Vulkan::GetVulkanFeaturesPath()); // Replace with your filename
    
    if (file.fail()) {
      CANDY_CORE_ASSERT(false, "Vulkan feature file could not be opened");
    }
    
    std::string line;
    while(std::getline(file, line)) {
      std::stringstream ss(line);
      
      std::string featureName;
      std::getline(ss, featureName, ',');
      
      std::string enabledValue;
      std::getline(ss, enabledValue, ',');
      
      bool featureEnabled = (enabledValue=="true");
      
      featureMap[featureName] = featureEnabled;
      
      if (featureEnabled)
      {
        CANDY_CORE_INFO("Vulkan Physical Device Feature: {} is enabled", featureName);
      }
      
    }
    
    file.close();
    
  }
  PhysicalDevice::PhysicalDevice(VkSurfaceKHR surface) : device(VK_NULL_HANDLE)
  {
    CANDY_PROFILE_FUNCTION();
    InitFeatures();
    uint32_t deviceCount=0;
    vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, nullptr);
    CANDY_CORE_ASSERT(deviceCount, "Failed to find GPUs with Vulkan support!");
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Vulkan::Instance(), &deviceCount, devices.data());
    
    std::vector<ScoredDevice> scoredDevices = RankSuitableDevices(surface, devices);
    
    CANDY_CORE_ASSERT(!scoredDevices.empty(), "Failed to find a suitable GPU!");
    int64_t currentScore = -1;
    for (const auto& d : scoredDevices)
    {
      CANDY_CORE_INFO("Found GPU with score {0}", d.score);
      
      if (d.score == currentScore)
      {
        CANDY_CORE_ASSERT(false, "Found multiple GPUs with the same score!");
      }
    }
    
    device = scoredDevices[0].device;
    
    vkGetPhysicalDeviceProperties(device, &properties);
    
    vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);
    maxAllocationSize=0;
    for (uint32_t i=0; i<memoryProperties.memoryHeapCount; i++)
    {
      if (memoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
      {
        maxAllocationSize = memoryProperties.memoryHeaps[i].size;
        break;
      }
    }
    CANDY_CORE_ASSERT(maxAllocationSize>0, "Failed to find a suitable GPU!");
    
    name = properties.deviceName;
    CANDY_CORE_INFO("Using GPU: {0}", name);
    
  }
  
 
  PhysicalDevice::PhysicalDevice(const PhysicalDevice& other) = default;
  
  
  bool PhysicalDevice::IsValid()const{return device != VK_NULL_HANDLE;}
  
  /*QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkSurfaceKHR surface)
  {
    return FindQueueFamilies(device, surface);
  }*/
  
  SwapChainSupportDetails PhysicalDevice::QuerySwapChainSupport(VkSurfaceKHR surface)
  {
    return QuerySwapChainSupport(device, surface);
  }
  
  uint32_t PhysicalDevice::GetQueueFamilyPropertyCount() const
  {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    return queueFamilyCount;
  }
  
  std::vector<VkQueueFamilyProperties> PhysicalDevice::GetQueueFamilyProperties() const
  {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    return queueFamilies;
  }
  
  bool PhysicalDevice::IsDeviceSuitable(VkSurfaceKHR surface)
  {
    return IsDeviceSuitable(device, surface);
  }
  
  bool PhysicalDevice::CheckDeviceExtensionSupport()
  {
    return CheckExtensionSupport(device);
  }
  
  bool PhysicalDevice::CheckExtensionSupport(VkPhysicalDevice device)
  {
    CANDY_PROFILE_FUNCTION();
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
    
    std::set<std::string> requiredExtensions(VulkanDeviceManager::DEVICE_EXTENSIONS.begin(), VulkanDeviceManager::DEVICE_EXTENSIONS.end());
    
    for (const auto& extension : availableExtensions) {
      requiredExtensions.erase(extension.extensionName);
    }
    
    return requiredExtensions.empty();
  }
  
  bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    //QueueFamilyIndices indices = FindQueueFamilies(device, surface);
    
    bool extensionsSupported = CheckExtensionSupport(device);
    
    if (extensionsSupported)
    {
      SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
      bool swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
      
      VkPhysicalDeviceShaderDrawParametersFeatures parametersFeatures{};
      
      parametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
      VkPhysicalDeviceFeatures2 supportedFeatures;
      supportedFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
      supportedFeatures.pNext = &parametersFeatures;
      vkGetPhysicalDeviceFeatures2(device, &supportedFeatures);
      
      bool isFeaturesSupported = CheckSupportedDeviceFeatures(supportedFeatures);
      
      return swapChainAdequate && isFeaturesSupported && parametersFeatures.shaderDrawParameters;
      //return indices.IsComplete() && swapChainAdequate && isFeaturesSupported && parametersFeatures.shaderDrawParameters;
    }
    return false;
    
    
  }
  
  long long int PhysicalDevice::RateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    if (! IsDeviceSuitable(device, surface))
    {
      return -1;
    }
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    long long int score=0;
    
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
      score += 1000;
    }
    score += deviceProperties.limits.maxMemoryAllocationCount;
    score += deviceProperties.limits.maxImageDimension2D;
    score += deviceProperties.limits.maxBoundDescriptorSets;
    score += deviceProperties.limits.maxStorageBufferRange;
    score += deviceProperties.limits.maxComputeSharedMemorySize;
    CANDY_CORE_INFO("Device {0} scored {1}", deviceProperties.deviceName, score);
    return score;
  }
  
  SwapChainSupportDetails PhysicalDevice::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    
    if (formatCount != 0) {
      details.formats.resize(formatCount);
      vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
    
    if (presentModeCount != 0) {
      details.presentModes.resize(presentModeCount);
      vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }
    
    return details;
  }
  /*QueueFamilyIndices PhysicalDevice::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
  {
    CANDY_PROFILE_FUNCTION();
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    
    // Find at least one queue family that supports VK_QUEUE_GRAPHICS_BIT
    int i = 0;
    for (const auto& queueFamily: queueFamilies)
    {
      if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
        indices.graphicsFamily = i;
      }
      if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
      {
        indices.computeFamily = i;
      }
      if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
      {
        indices.transferFamily = i;
      }
      
      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
      if (presentSupport)
      {
        indices.presentFamily = i;
      }
      if (indices.IsComplete())
      {
        break;
      }
      i++;
    }
    
    return indices;
  }*/
  
  const char* PhysicalDevice::GetName()const
  {
    return properties.deviceName;
  }
  uint32_t PhysicalDevice::GetDriverVersion()const
  {
    return properties.driverVersion;
  }
  uint32_t PhysicalDevice::GetApiVersion()const
  {
    return properties.apiVersion;
  }
  uint32_t PhysicalDevice::GetVendorID()const
  {
    return properties.vendorID;
  }
  uint32_t PhysicalDevice::GetDeviceID()const
  {
    return properties.deviceID;
  }
  size_t PhysicalDevice::GetMinUniformBufferOffsetAlignment()const
  {
    return properties.limits.minUniformBufferOffsetAlignment;
  }
  uint32_t PhysicalDevice::GetMaxPushConstantSize()const
  {
    return properties.limits.maxPushConstantsSize;
  }
  uint32_t PhysicalDevice::GetMaxDynamicUniformBufferCount()const
  {
    return properties.limits.maxDescriptorSetUniformBuffersDynamic;
  }
  
  uint32_t PhysicalDevice::GetMaxUniformBufferSize()const
  {
    return properties.limits.maxUniformBufferRange;
  }
  size_t PhysicalDevice::GetMaxAllocationSize()const
  {
    return maxAllocationSize;
  }
  VkPhysicalDeviceProperties PhysicalDevice::GetProperties()const
  {
    
    return properties;
  }
  
  size_t PhysicalDevice::PadUniformBufferSize(size_t originalSize)const
  {
    CANDY_PROFILE_FUNCTION();
    size_t minUboAlignment = GetMinUniformBufferOffsetAlignment();
    size_t alignedSize = originalSize;
    if (minUboAlignment > 0)
    {
      alignedSize = (alignedSize + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }
    return alignedSize;
  }
}