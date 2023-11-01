#include <gum/render/Renderer.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/font/Font.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include "gum/GumSystem.hpp"
#include <gum/render/RectRenderer.hpp>
#include <candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp>
namespace Candy::Gum
{
  using namespace Math;
  
  struct GumRenderData
  {
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    
    SharedPtr<Graphics::Texture> whiteTexture;
    std::array<SharedPtr<Graphics::Texture>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture, 1 = statue texture
    SceneGraph* currentScene=nullptr;
    RectRenderer* rectRenderer=nullptr;
    
    
  };
  static GumRenderData data;
  
  void Renderer::Init()
  {
    CANDY_CORE_INFO("Initializing Renderer");
    data.whiteTexture = Graphics::Texture::White();
    
    data.textureSlots[0] = data.whiteTexture;
    data.rectRenderer = new RectRenderer(Graphics::Renderer::GetGumPassIndex(), GumRenderData::maxQuads);
    
    CANDY_CORE_INFO("Initialized Renderer");
  }
  
  
  void Renderer::Flush()
  {
    if (data.currentScene == nullptr)
    {
      return;
    }
    // Bind textures
    std::vector<VkDescriptorImageInfo> imageInfos{};
    for (uint32_t i=0; i<data.textureSlotIndex; i++)
    {
      CANDY_CORE_ASSERT(data.textureSlots[i] != nullptr);
      
      VkDescriptorImageInfo imageInfo = data.textureSlots[i]->GetDescriptorImageInfo();
      imageInfos.push_back(imageInfo);
    }
    for (uint32_t i=data.textureSlotIndex; i<GumRenderData::maxTextureSlots; i++)
    {
      VkDescriptorImageInfo imageInfo = data.whiteTexture->GetDescriptorImageInfo();
      imageInfos.push_back(imageInfo);
    }
    Graphics::DescriptorBuilder textureBuilder = Graphics::DescriptorBuilder::Begin();
    textureBuilder.AddImageArrayWrite(0, imageInfos, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, Graphics::MATERIAL_SET);
    textureBuilder.Write();
    data.rectRenderer->Flush(data.currentScene->GetSceneSize());
    
    
  }
  void Renderer::BeginScene(SceneGraph& sceneGraph)
  {
    data.currentScene = &sceneGraph;
    data.rectRenderer->Reset();
  }
  void Renderer::EndScene()
  {
    Flush();
  }
  
  
  void Renderer::SubmitRectangle(const Math::Matrix3& transform, const Rectangle& rectangle, int depthIndex)
  {
    auto texture = rectangle.fill.texture;
    int textureIndex=0;
    if (texture)
    {
      bool found = false;
      
      for (int i=0; i<data.textureSlotIndex; i++)
      {
        if (*data.textureSlots[i] == *texture)
        {
          found = true;
          textureIndex = i;
          break;
        }
      }
      if (! found)
      {
        CANDY_CORE_ASSERT(data.textureSlotIndex < data.maxTextureSlots, "Texture slots are full");
        data.textureSlots[data.textureSlotIndex] = texture;
        textureIndex = data.textureSlotIndex;
        data.textureSlotIndex++;
      }
    }
    else
    {
      textureIndex = 0;
    }
    data.rectRenderer->Submit(rectangle.GetBoundsInScene().GetBottomLeft(), rectangle.GetSize(), rectangle.strokeWidth, rectangle.stroke, rectangle.fill, rectangle.arcSize, textureIndex);
  }
}