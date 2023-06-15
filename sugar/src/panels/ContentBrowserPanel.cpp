#include "ContentBrowserPanel.hpp"
#include <Candy/CandyEngine.hpp>
namespace Candy
{
    ContentBrowserPanel::ContentBrowserPanel() : baseDirectory(Project::GetAssetDirectory()), currentDirectory(baseDirectory)
    {
        directoryIcon = Graphics::Texture::Create("sugar/Resources/Icons/ContentBrowser/DirectoryIcon.png");
        fileIcon = Graphics::Texture::Create("sugar/Resources/Icons/ContentBrowser/FileIcon.png");
    }
    
    void ContentBrowserPanel::OnRenderUI()
    {
        /*CANDY_CORE_INFO("START CONTENT BROWSER PANEL ONRENDERUI");
        ImGui::Begin("Content Browser");
        CANDY_CORE_INFO("BEGAN IMGUI");
        if (currentDirectory != baseDirectory)
        {
            CANDY_CORE_INFO("CURRENT DIRECTORY NOT BASE DIRECTORY");
            if (ImGui::Button("<-"))
            {
                CANDY_CORE_INFO("IMGUI BUTTON");
                currentDirectory = currentDirectory.parent_path();
            }
        }
        
        CANDY_CORE_INFO("COMPLETED CONTENT BROWSER PANEL CURRENT DIRECTORY");
        
        static float padding = 16.0f;
        static float thumbnailSize = 128.0f;
        float cellSize = thumbnailSize + padding;
        
        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;
        
        ImGui::Columns(columnCount, nullptr, false);
        
        for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
        {
            const auto& path = directoryEntry.path();
            std::string filenameString = path.filename().string();
            
            ImGui::PushID(filenameString.c_str());
            SharedPtr<Texture> icon = directoryEntry.is_directory() ? directoryIcon : fileIcon;
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
            
            if (ImGui::BeginDragDropSource())
            {
                std::filesystem::path relativePath(path);
                const wchar_t* itemPath = relativePath.c_str();
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
                ImGui::EndDragDropSource();
            }
            
            ImGui::PopStyleColor();
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryEntry.is_directory())
                    currentDirectory /= path.filename();
                
            }
            ImGui::TextWrapped(filenameString.c_str());
            
            ImGui::NextColumn();
            
            ImGui::PopID();
        }
        
        ImGui::Columns(1);
        
        ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
        ImGui::SliderFloat("Padding", &padding, 0, 32);
        
        // TODO: status bar
        ImGui::End();*/
    }
}