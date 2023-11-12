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
    directoryIcon = Texture::Create(CandyEngine::GetInternalAssetsDirectory() / "icons/DirectoryIcon.png");
    fileIcon = Texture::Create(CandyEngine::GetInternalAssetsDirectory() / "icons/FileIcon.png");
    descriptorSets.resize(2);
    
    
    descriptorSets[0] = ImGui_ImplVulkan_AddTexture(directoryIcon->GetSampler(), directoryIcon->GetImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    descriptorSets[1] = ImGui_ImplVulkan_AddTexture(fileIcon->GetSampler(), fileIcon->GetImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    
    
  
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
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
      filePopupType = FileMenuPopupType::CreateFile;
    }
    if (ImGui::BeginTable("##content_browser", columnCount, ImGuiTableFlags_Reorderable))
    {
     
      int column = 0;
      for (const auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
      {
        if(column % columnCount == 0)
          ImGui::TableNextRow();
        
        ImGui::TableSetColumnIndex(column % columnCount);
        const auto& path = directoryEntry.path();
        std::string fileName = path.filename().string();
        ImGui::PushID(fileName.c_str());
        
        VkDescriptorSet icon = directoryEntry.is_directory() ? descriptorSets[0] : descriptorSets[1];
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton(fileName.c_str(), icon, ImVec2{thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
        
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
          CANDY_CORE_INFO("Right clicked path: {}", path.string());
          filePopupType = FileMenuPopupType::ModifyFile;
          popupPath = path;
        }
        else if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
          if (directoryEntry.is_directory())
          {
            currentDirectory /= path.filename();
            
          }
        }
        if (ImGui::BeginDragDropSource())
        {
          const wchar_t* itemPath = path.c_str();
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