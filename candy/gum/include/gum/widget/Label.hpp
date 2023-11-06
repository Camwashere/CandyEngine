#pragma once
#include <gum/widget/Widget.hpp>
//#include <candy/graphics/font/Font.hpp>
#include <gum/text/Text.hpp>
namespace Candy::Gum
{
  class Label : public Widget
  {
  public:
    Text text;
    float wrap=1.0f;
    /*std::string text;
    Paint fill;
    float kerning = 0.0f;
    float lineSpacing = 0.0f;*/
    
  protected:
    virtual void OnRender() override;
    
  public:
    Label();
    explicit Label(const std::string& text);
    
    
    
  public:
    
    std::string GetText()const;
    void SetText(const std::string& text);
    
    
    
    void SetFill(const Paint& value);
    Paint GetFill()const;
    
    float GetKerning()const;
    void SetKerning(float value);
    float GetLineSpacing()const;
    void SetLineSpacing(float value);
    
  };
}