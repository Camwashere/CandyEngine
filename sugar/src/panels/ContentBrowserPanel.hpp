#pragma once
#include <filesystem>
#include <Candy/Graphics.hpp>
namespace Candy {
    
    class ContentBrowserPanel
    {
    private:
        std::filesystem::path baseDirectory;
        std::filesystem::path currentDirectory;
        
        SharedPtr<Graphics::Texture> directoryIcon;
        SharedPtr<Graphics::Texture> fileIcon;
        
        
    public:
        ContentBrowserPanel();
        
        void OnRenderUI();
    
    };
    
}