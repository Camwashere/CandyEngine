#include <gum/widget/Label.hpp>
#include <utility>
#include <gum/render/Renderer.hpp>
namespace Candy::Gum
{
  Label::Label()
  {
    SetBackgroundFill(Color::white);
  }
  Label::Label(const std::string& text) : text(text)
  {
    SetBackgroundFill(Color::white);
  }
  
  
  void Label::OnRender()
  {
    Renderer::SubmitShape(GetTransform(), GetShape());
    text.position = GetBoundsInScene().GetPosition();
    text.size = GetSize();
    if (text.GetFont() == nullptr)
      text.SetFont(Graphics::Font::Default());
    text.Render(wrap);
  }
  
  std::string Label::GetText()const
  {
    return text.GetText();
  }
  void Label::SetText(const std::string& value)
  {
    text.SetText(value);
  }
  
  
  
  void Label::SetFill(const Paint& value)
  {
    text.SetFill(value);
  }
  Paint Label::GetFill()const
  {
    return text.GetFill();
  }
  
  float Label::GetKerning()const
  {
    return text.GetKerning();
  }
  void Label::SetKerning(float value)
  {
    text.SetKerning(value);
  }
  float Label::GetLineSpacing()const
  {
    return text.GetLineSpacing();
  }
  void Label::SetLineSpacing(float value)
  {
    text.SetLineSpacing(value);
  }
}