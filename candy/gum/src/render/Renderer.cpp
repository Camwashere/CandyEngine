#include <gum/render/Renderer.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/font/Font.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include "gum/GumSystem.hpp"
#include <gum/render/RectRenderer.hpp>
namespace Candy::Gum
{
  using namespace Math;
  
  struct GumRenderData
  {
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    
    SceneGraph* currentScene=nullptr;
    RectRenderer* rectRenderer=nullptr;
    
    
  };
  static GumRenderData data;
  
  void Renderer::Init()
  {
    CANDY_CORE_INFO("Initializing Renderer");
    data.rectRenderer = new RectRenderer(Graphics::Renderer::GetGumPassIndex(), GumRenderData::maxQuads);
    
    CANDY_CORE_INFO("Initialized Renderer");
  }
  
  
  void Renderer::Flush()
  {
    if (data.currentScene == nullptr)
    {
      return;
    }
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
    data.rectRenderer->Submit(rectangle.GetBoundsInScene().GetBottomLeft(), rectangle.GetSize(), rectangle.GetStrokeWidth(), rectangle.GetStrokeColor(), rectangle.GetFillColor(), rectangle.GetArcSize());
  }
}