#include <gum/style/Paint.hpp>
#include <utility>

namespace Candy::Gum
{
  Paint::Paint() : color(Color::white), texture(nullptr)
  {
  
  }
  Paint::Paint(const Color& color) : color(color)
  {
  
  }
  Paint::Paint(SharedPtr<Graphics::Texture> texture) : texture(std::move(texture))
  {
  
  }
  Paint::Paint(const Color& color, SharedPtr<Graphics::Texture> texture) : color(color), texture(std::move(texture))
  {
  
  }
  
  
}