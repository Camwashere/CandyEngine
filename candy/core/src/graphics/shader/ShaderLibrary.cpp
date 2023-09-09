#include "candy/graphics/shader/ShaderLibrary.hpp"
#include "CandyPch.hpp"
#include <utility>
#include <filesystem>
#include <candy/graphics/Vulkan.hpp>

namespace Candy::Graphics
{
  ShaderLibrary::ShaderLibrary()
  {
    shaderSets.resize(3);
  }
    ShaderLibrary::ShaderLibrary(std::filesystem::path  cacheDir, std::filesystem::path  internalShaderDir, bool createDirectoriesIfNeeded) : cacheDirectory(std::move(cacheDir)), internalShaderDirectory(std::move(internalShaderDir))
    {
        if (createDirectoriesIfNeeded)
        {
            if (! HasCacheDirectory())
            {
                std::filesystem::create_directories(cacheDirectory);
            }
            if (! HasInternalShaderDirectory())
            {
                std::filesystem::create_directories(internalShaderDirectory);
            }
        }
        CANDY_CORE_ASSERT(std::filesystem::exists(cacheDirectory), "Cache directory does not exist!");
        CANDY_CORE_ASSERT(std::filesystem::exists(internalShaderDirectory), "Internal shader directory does not exist!");
        shaderSets.resize(3);
        
    }
    
    ShaderLibrary ShaderLibrary::instance;
    
    const std::filesystem::path& ShaderLibrary::GetCacheDirectory()const{return cacheDirectory;}
    const std::filesystem::path& ShaderLibrary::GetInternalShaderDirectory()const{return internalShaderDirectory;}
  
  void ShaderLibrary::AddShader(const SharedPtr<Shader>& shader)
  {
      for (const auto& set : shader->GetLayout().sets)
      {
        auto& libSet = shaderSets[set.GetSet()];
        for (const auto& block : set.blocks)
        {
          if (!libSet.HasBlockBinding(block.binding))
          {
            libSet.AddBlock(block);
          }
        }
        for (const auto& tex : set.textures)
        {
          if (!libSet.HasTextureBinding(tex.binding))
          {
            libSet.AddTexture(tex);
          }
        }
      }
      shaders.push_back(shader);
  }
  void ShaderLibrary::Reload()
  {
      for (const auto& set : shaderSets)
      {
        CANDY_CORE_INFO("Set: {0}, bindings: {1}", set.GetSet(), set.blocks.size() + set.textures.size());
      }
      
      for (auto& shader : shaders)
      {
        shader->Bake();
      }
      
      
        
  }
  VkDescriptorType GetDescriptorType(size_t setIndex)
  {
    switch(setIndex)
    {
      case 0:
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
      case 1:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
      default:
      CANDY_CORE_ASSERT(false, "Invalid descriptor set index!");
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
  }
  
  std::vector<VkDescriptorSetLayout> ShaderLibrary::BakeDescriptorSetLayouts(uint8_t renderPassIndex)
  {
    const int FRAME_OVERLAP = 2;
    std::vector<VkDescriptorSetLayout> layouts;
    
    size_t LAYOUT_NUM = shaderSets.size();
    layouts.resize(LAYOUT_NUM);
    //bool skipObject=renderPassIndex == Renderer::GetOverlayPassIndex();
    
    for (size_t i = 0; i<LAYOUT_NUM; i++)
    {
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      
      /*if (skipObject && i==1)
      {
        continue;
      }*/
      
      for (const auto &block: shaderSets[i].blocks)
      {
        
        builder.AddBinding(block.binding, GetDescriptorType(i), ShaderData::StageToVulkan(block.stage));
      }
      for (const auto &tex: shaderSets[i].textures)
      {
        builder.AddBinding(tex.binding, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, ShaderData::StageToVulkan(tex.stage), tex.arraySize);
      }
      layouts[i] = builder.BuildLayout();
      for (int f = 0; f<FRAME_OVERLAP; f++)
      {
        CANDY_CORE_ASSERT(builder.AllocateDescriptorSet(&Vulkan::GetCurrentContext().GetFrame(f).GetDescriptorSet(i, renderPassIndex), layouts[i]), "Failed to allocate descriptor set!");
      }
    }
    return layouts;
  }
    
    bool ShaderLibrary::IsValid()const
    {
        return HasCacheDirectory() && HasInternalShaderDirectory();
    }
    bool ShaderLibrary::HasCacheDirectory()const
    {
        return std::filesystem::exists(cacheDirectory);
    }
    bool ShaderLibrary::HasInternalShaderDirectory()const
    {
        return std::filesystem::exists(internalShaderDirectory);
    }
}