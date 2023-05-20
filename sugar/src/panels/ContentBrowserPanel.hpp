#pragma once
#include <filesystem>
#include <Candy/Graphics.hpp>
namespace Candy {
    
    class ContentBrowserPanel
    {
    public:
        ContentBrowserPanel();
        
        void OnImGuiRender();
    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;
        
        SharedPtr<Graphics::Texture> m_DirectoryIcon;
        SharedPtr<Graphics::Texture> m_FileIcon;
    };
    
}