#pragma once
#include <candy/graphics/Color.hpp>
#include <candy/graphics/texture/Texture.hpp>
namespace Candy::Gum
{
  struct Paint
  {
    Color color=Color::white;
    SharedPtr<Graphics::Texture> texture;
    
    Paint();
    Paint(const Color& color);
    Paint(SharedPtr<Graphics::Texture> texture);
    Paint(const Color& color, SharedPtr<Graphics::Texture> texture);
    
    
    
  };
}