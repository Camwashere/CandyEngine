#pragma once
#include <filesystem>
#include <CandyPch.hpp>
#include "candy/graphics/texture/Texture.hpp"
#include <candy/graphics/vulkan/ImageView.hpp>
namespace Candy
{
  class ContentBrowserPanel
  {
  private:
    struct IconData
    {
      SharedPtr<Graphics::Texture> texture;
      VkDescriptorSet descriptorSet;
      
      explicit IconData(const std::filesystem::path& iconPath);
      
      
      static SharedPtr<IconData> Create(const std::filesystem::path& iconPath);
      
    };
    std::filesystem::path rootDirectory;
    std::filesystem::path currentDirectory;
    SharedPtr<IconData> directoryIcon;
    SharedPtr<IconData> fileIcon;
    SharedPtr<IconData> imageIcon;
    //std::vector<VkDescriptorSet> descriptorSets;
    
    std::filesystem::path popupPath;
    
    float thumbnailSize = 128.0f;
    float padding = 16.0f;
    
    enum class FileMenuPopupType
    {
      None=0,
      CreateFile=1,
      ModifyFile=2,
    };
    
    FileMenuPopupType filePopupType = FileMenuPopupType::None;
    
  private:
    void RenderFileModifyMenu();
    void RenderFileCreateMenu();
    VkDescriptorSet DetermineIconForFile(const std::filesystem::directory_entry& entry);
    
  public:
    explicit ContentBrowserPanel(std::filesystem::path  contentRoot);
    void OnRenderUI();
    void OnDetach();
    
  public:
    void SetThumbnailSize(float value);
    void SetPaddingSize(float value);
    [[nodiscard]] float GetThumbnailSize()const;
    [[nodiscard]] float GetPaddingSize()const;
  };
}