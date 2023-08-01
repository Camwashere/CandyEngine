#include <editor/panels/ContentBrowserPanel.hpp>
#include <utility>
#include <candy/graphics/RenderCommand.hpp>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_vulkan.h"
namespace Candy
{
  using namespace Graphics;
  ContentBrowserPanel::ContentBrowserPanel(std::filesystem::path  contentRoot) : rootDirectory(std::move(contentRoot)), currentDirectory(rootDirectory)
  {
    /*Texture directoryIconTex;
    Texture fileIconTex;
    descriptorSets.resize(2);
    directoryIconTex.Load("assets/icons/DirectoryIcon.png");
    fileIconTex.Load("assets/icons/FileIcon.png");
    directoryIcon = CreateSharedPtr<ImageView>();
    fileIcon = CreateSharedPtr<ImageView>();
    directoryIcon->Set(directoryIconTex);
    fileIcon->Set(fileIconTex);
    descriptorSets[0] = ImGui_ImplVulkan_AddTexture(directoryIcon->GetSampler(), *directoryIcon, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    descriptorSets[1] = ImGui_ImplVulkan_AddTexture(fileIcon->GetSampler(), *fileIcon, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);*/
    
    
    
  
  }
  
  void ContentBrowserPanel::OnRenderUI()
  {
    /*ImGui::Begin("Content Browser");
    
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
    
    ImGui::Columns(columnCount, nullptr, false);
    
    for (auto& directoryEntry : std::filesystem::directory_iterator(currentDirectory))
    {
      const auto& path = directoryEntry.path();
      std::string fileName = path.filename().string();
      
      ImGui::PushID(fileName.c_str());
      VkDescriptorSet icon = directoryEntry.is_directory() ? descriptorSets[0] : descriptorSets[1];
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
      ImGui::ImageButton(icon, ImVec2{thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
      
      ImGui::PopStyleColor();
      if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
      {
        if (directoryEntry.is_directory())
        {
          currentDirectory /= path.filename();
        }
      }
      
      ImGui::TextWrapped(fileName.c_str());
      ImGui::NextColumn();
      ImGui::PopID();
    }
    ImGui::Columns(1);
    ImGui::End();*/
    
    /*ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ImGui::ImageButton(descriptorSets[0], ImVec2{viewportPanelSize.x, viewportPanelSize.y});
    ImGui::End();*/
    //ImGui::Image(descriptorSets[1], ImVec2{viewportPanelSize.x, viewportPanelSize.y});
  
  }
}