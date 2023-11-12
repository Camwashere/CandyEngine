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
    std::filesystem::path rootDirectory;
    std::filesystem::path currentDirectory;
    SharedPtr<Graphics::Texture> directoryIcon;
    SharedPtr<Graphics::Texture> fileIcon;
    std::vector<VkDescriptorSet> descriptorSets;
    
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