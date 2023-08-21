#include <editor/panels/ContentBrowserPanel.hpp>
#include <utility>
#include <candy/graphics/RenderCommand.hpp>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_vulkan.h"
#include <candy/graphics/Vulkan.hpp>
namespace Candy
{
  using namespace Graphics;
  ContentBrowserPanel::ContentBrowserPanel(std::filesystem::path  contentRoot) : rootDirectory(std::move(contentRoot)), currentDirectory(rootDirectory)
  {
    
    directoryImage = new Texture("assets/icons/DirectoryIcon.png");
    fileImage = new Texture("assets/icons/FileIcon.png");
    descriptorSets.resize(2);
    
    directoryIcon = CreateSharedPtr<ImageView>();
    fileIcon = CreateSharedPtr<ImageView>();
    
    directoryIcon->Set(*directoryImage);
    fileIcon->Set(*fileImage);
    descriptorSets[0] = ImGui_ImplVulkan_AddTexture(directoryIcon->GetSampler(), *directoryIcon, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    descriptorSets[1] = ImGui_ImplVulkan_AddTexture(fileIcon->GetSampler(), *fileIcon, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    
    
    
  
  }
  
  void ContentBrowserPanel::OnRenderUI()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_None;
    ImGui::Begin("Content Browser", nullptr, flags);
    
    if (currentDirectory != rootDirectory)
    {
      if (ImGui::Button("<-"))
      {
        currentDirectory = currentDirectory.parent_path();
      }
    }
    static float padding = 16.0f;
    static float thumbnailSize = 128.0f;
    float cellSize = thumbnailSize + padding;
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1)
      columnCount = 1;
    ImGui::BeginTable("##content_browser", columnCount, ImGuiTableFlags_Reorderable);
    if (showFileMenuPopup)
    {
      ImGui::OpenPopup("File Options");
      showFileMenuPopup=false;
    }
    RenderFileMenu();
    for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
    {
      const auto& path = directoryEntry.path();
      std::string fileName = path.filename().string();
      
      ImGui::PushID(fileName.c_str());
      VkDescriptorSet icon = directoryEntry.is_directory() ? descriptorSets[0] : descriptorSets[1];
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
      ImGui::ImageButton(icon, ImVec2{thumbnailSize, thumbnailSize}, {0, 0}, {1, 1});
      
      ImGui::PopStyleColor();
      
      /*if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
      {
        ShowFileMenu(currentDirectory / path.filename());
      }*/
      
      
      if (ImGui::IsItemHovered())
      {
        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
          ShowFileMenu(currentDirectory / path.filename());
        }
        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
          if (directoryEntry.is_directory())
          {
            currentDirectory /= path.filename();
            
          }
        }
      }
      
      
      ImGui::TextWrapped(fileName.c_str());
      ImGui::TableNextColumn();
      ImGui::PopID();
    }
    ImGui::EndTable();
    ImGui::End();
    
  }
  
  void ContentBrowserPanel::ShowFileMenu(const std::filesystem::path& path)
  {
    //CANDY_CORE_INFO("SHOW FILE MENU FOR PATH: {}", path.string());
    CANDY_CORE_ASSERT(std::filesystem::exists(path));
    popupPath = path;
    showFileMenuPopup=true;
    
  }
  void ContentBrowserPanel::RenderFileMenu()
  {
    if (ImGui::BeginPopup("File Options"))
    {
      if (std::filesystem::is_directory(popupPath))
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
      }
      else
      {
        if (ImGui::MenuItem("Delete"))
        {
          std::filesystem::remove_all(popupPath);
        }
      }
      
      
      ImGui::EndPopup();
    }
  }
  
  void ContentBrowserPanel::OnDetach()
  {
    //Vulkan::DeletionQueue().Delete(directoryIcon.get());
    //Vulkan::DeletionQueue().Delete(fileIcon.get());
  }
}