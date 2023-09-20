#include <gum/base/GumRenderer.hpp>
#include <candy/graphics/VertexArray.hpp>
#include "candy/graphics/texture/Texture.hpp"
namespace Candy::Gum
{
  using namespace Graphics;
  using namespace Math;
  
  
  
  struct GumData
  {
    GumTree tree;
    GumRenderer::Stats stats{};
  };
  
  void GumRenderer::Init()
  {
  
  }
}