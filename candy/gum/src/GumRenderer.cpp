#include <gum/GumRenderer.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/graphics/shader/Shader.hpp>
#include <candy/graphics/VertexArray.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/font/Font.hpp>
#include <candy/graphics/font/MSDFData.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <gum/GumInstance.hpp>
#include <gum/render/RectRenderer.hpp>
namespace Candy::Gum
{
  using namespace Graphics;
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
  
  void GumRenderer::Init()
  {
    CANDY_CORE_INFO("Initializing GumRenderer");
    data.rectRenderer = new RectRenderer(Renderer::GetGumPassIndex(), GumRenderData::maxQuads);
    
    CANDY_CORE_INFO("Initialized GumRenderer");
  }
  
  
  void GumRenderer::Flush()
  {
    if (data.currentScene == nullptr)
    {
      return;
    }
    data.rectRenderer->Flush(data.currentScene->GetSceneSize());

    
  }
  void GumRenderer::BeginScene(SceneGraph& sceneGraph)
  {
    data.currentScene = &sceneGraph;
    data.rectRenderer->Reset();
  }
  void GumRenderer::EndScene()
  {
    Flush();
  }
  
  
  void GumRenderer::SubmitRectangle(const Math::Matrix3& transform, const Rectangle& rectangle, int depthIndex)
  {
    data.rectRenderer->Submit(rectangle);
  }
  
}