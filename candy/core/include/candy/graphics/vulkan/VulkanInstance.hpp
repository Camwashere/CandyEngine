#pragma once
#include "CandyPch.hpp"
#include "VulkanDebugManager.hpp"


struct GLFWwindow;
namespace Candy::Graphics
{
    class GraphicsContext;
    
    class VulkanInstance
    {

    private:
        VkInstance instance;
        UniquePtr<VulkanDebugManager> debugManager;

        
        
    private:
        void CreateInstance();
        
    public:
        VulkanInstance();
        void Shutdown();
        
    
        
    public:

        static std::vector<const char*> GetRequiredExtensions();
        static std::vector<std::string> GetAvailableExtensions();
        static void DisplayAvailableExtensions();

        
    private:
      friend class Vulkan;
        
        
        
        
    };
    
}