#pragma once
#include <filesystem>
#include <CandyPch.hpp>
#include <candy/graphics/Texture.hpp>
#include <candy/graphics/vulkan/ImageView.hpp>
namespace Candy
{
  class ContentBrowserPanel
  {
  private:
    std::filesystem::path rootDirectory;
    std::filesystem::path currentDirectory;
    
    SharedPtr<Graphics::ImageView> directoryIcon;
    SharedPtr<Graphics::ImageView> fileIcon;
    std::vector<VkDescriptorSet> descriptorSets;
  public:
    explicit ContentBrowserPanel(std::filesystem::path  contentRoot);
    
    void OnRenderUI();
  };
}