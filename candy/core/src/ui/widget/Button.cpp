#include <candy/ui/widget/Button.hpp>

namespace Candy::UI
{
  Button::Button(std::string text, Math::Vector2 pos, Math::Vector2 size) : text(std::move(text)), position(pos), size(size)
  {
  
  }
}