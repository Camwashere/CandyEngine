#include <editor/panels/ContentBrowserPanel.hpp>
#include <utility>
#include <candy/graphics/RenderCommand.hpp>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/Vulkan.hpp>
#include <CandyEngine.hpp>
namespace Candy
{
  using namespace Graphics;
  ContentBrowserPanel::ContentBrowserPanel(std::filesystem::path  contentRoot) : rootDirectory(std::move(contentRoot)), currentDirectory(rootDirectory)
  {
    CANDY_PROFILE_FUNCTION();
    directoryIcon = IconData::Create(CandyEngine::GetInternalAssetsDirectory() / "icons/DirectoryIcon.png");
    fileIcon = IconData::Create(CandyEngine::GetInternalAssetsDirectory() / "icons/FileIcon.png");
    imageIcon = IconData::Create(CandyEngine::GetInternalAssetsDirectory() / "icons/ImageIcon.png");
    
    CANDY_CORE_INFO("Root Directory: {}, current directory: {}", rootDirectory.string(), currentDirectory.string());
    
  }
  
  ContentBrowserPanel::IconData::IconData(const std::filesystem::path& iconPath)
  {
    CANDY_PROFILE_FUNCTION();
    texture = Texture::Create(iconPath);
    descriptorSet = ImGui_ImplVulkan_AddTexture(texture->GetSampler(), texture->GetImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }
  SharedPtr<ContentBrowserPanel::IconData> ContentBrowserPanel::IconData::Create(const std::filesystem::path& iconPath)
  {
    return CreateSharedPtr<IconData>(iconPath);
  }
  void ContentBrowserPanel::OnRenderUI()
  {
    CANDY_PROFILE_FUNCTION();
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;
    ImGui::Begin("Content Browser", nullptr, flags);
    
    if (currentDirectory != rootDirectory)
    {
      if (ImGui::Button("<-"))
      {
        currentDirectory = currentDirectory.parent_path();
      }
    }
    float cellSize = thumbnailSize + padding;
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1)
      columnCount = 1;
    
    switch(filePopupType)
    {
      case FileMenuPopupType::None:
        break;
      case FileMenuPopupType::CreateFile:
        ImGui::OpenPopup("File Create Menu");
        filePopupType = FileMenuPopupType::None;
        break;
      case FileMenuPopupType::ModifyFile:
        ImGui::OpenPopup("File Modify Menu");
        filePopupType = FileMenuPopupType::None;
        break;
    }
    RenderFileCreateMenu();
    RenderFileModifyMenu();
    popupPath = currentDirectory;
    filePopupType = FileMenuPopupType::None;
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
      filePopupType = FileMenuPopupType::CreateFile;
    }
    if (ImGui::BeginTable("##content_browser", columnCount, ImGuiTableFlags_Reorderable))
    {
     
      int column = 0;
      for (const auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
      {
        const std::filesystem::path& path = directoryEntry.path();
        std::string fileName = path.filename().string();
        if(column % columnCount == 0)
          ImGui::TableNextRow();
        
        ImGui::TableSetColumnIndex(column % columnCount);
        
        ImGui::PushID(fileName.c_str());
        
        //VkDescriptorSet icon = directoryEntry.is_directory() ? descriptorSets[0] : descriptorSets[1];
        VkDescriptorSet icon = DetermineIconForFile(directoryEntry);
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        bool clickedImgBtn = ImGui::ImageButton(fileName.c_str(), icon, ImVec2{thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
        
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
          if (directoryEntry.is_directory())
          {
            std::filesystem::path potentialPath = currentDirectory / fileName;
            if (std::filesystem::exists(potentialPath))
            {
              currentDirectory = potentialPath;
            }
            else
            {
              CANDY_CORE_WARN("Directory does not exist: {}", potentialPath.string());
            }
            
            
          }
        }
        
        
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
          filePopupType = FileMenuPopupType::ModifyFile;
          popupPath = path;
        }
        
        if (ImGui::BeginDragDropSource())
        {
          const auto* itemPath = path.c_str();
          ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
          ImGui::EndDragDropSource();
        }
        ImGui::PopStyleColor();
        
        
        
        ImGui::TextWrapped(fileName.c_str());
        ImGui::PopID();
        
        column++;
      }
      ImGui::EndTable();
    }
    
    ImGui::End();
    
  }
  
 
  void ContentBrowserPanel::RenderFileModifyMenu()
  {
    CANDY_PROFILE_FUNCTION();
    if (ImGui::BeginPopup("File Modify Menu"))
    {
      if (ImGui::MenuItem("Delete"))
      {
        std::filesystem::remove_all(popupPath);
      }
      if (ImGui::MenuItem("Rename"))
      {
        CANDY_CORE_INFO("Rename file: {}", popupPath.string());
      }
      
      
      ImGui::EndPopup();
    }
  }
  
  void ContentBrowserPanel::RenderFileCreateMenu()
  {
    if (ImGui::BeginPopup("File Create Menu"))
    {
      if (ImGui::BeginMenu("New"))
      {
        if (ImGui::MenuItem("File"))
        {
          std::ofstream(popupPath / "New File").close();
        }
        if (ImGui::MenuItem("Folder"))
        {
          std::filesystem::create_directory(popupPath / "New Folder");
        }
        ImGui::EndMenu();
      }
      
      ImGui::EndPopup();
    }
    
  }
  VkDescriptorSet ContentBrowserPanel::DetermineIconForFile(const std::filesystem::directory_entry& entry)
  {
    if (entry.is_directory())
    {
      return directoryIcon->descriptorSet;
    }
    std::string ext = entry.path().extension().string();
    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
    {
      return imageIcon->descriptorSet;
    }
    return fileIcon->descriptorSet;
  
  }
  void ContentBrowserPanel::OnDetach()
  {
    //Vulkan::DeletionQueue().Delete(directoryIcon.get());
    //Vulkan::DeletionQueue().Delete(fileIcon.get());
  }
  
  void ContentBrowserPanel::SetThumbnailSize(float value)
  {
    thumbnailSize = value;
  }
  void ContentBrowserPanel::SetPaddingSize(float value)
  {
    padding = value;
  }
  float ContentBrowserPanel::GetThumbnailSize()const
  {
    return thumbnailSize;
  }
  float ContentBrowserPanel::GetPaddingSize()const
  {
    return padding;
  }
}