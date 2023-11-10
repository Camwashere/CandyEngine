#pragma once
#include <string>
#include <gum/style/Paint.hpp>
//#include <candy/graphics/font/Font.hpp>
#include <candy/math/geometry/Bounds2D.hpp>
#include <gum/font/FontInternal.hpp>
namespace Candy::Gum
{
  class Text
  {
  public:
    Math::Vector2 position;
    Math::Vector2 size;
    
  private:
    std::string text;
    Paint fill;
    SharedPtr<FontInternal> font;
    float kerning = 0.0f;
    float letterSpacing = 0.0f;
    float lineSpacing = 0.0f;
    
  public:
    Text();
    explicit Text(const std::string& text);
    Text(const std::string& text, const Paint& fill);
    
  public:
    void Render(float wrap);
    SharedPtr<FontInternal> GetFont()const;
    void SetFont(SharedPtr<FontInternal> font);
    [[nodiscard]] float GetFontSize()const;
    void SetFontSize(float value);
    
    [[nodiscard]] Math::Vector2 GetSize()const;
    [[nodiscard]] Math::Vector2 GetPosition()const;
    [[nodiscard]] std::string GetText()const;
    void SetText(const std::string& text);
    
    void SetFill(const Paint& value);
    [[nodiscard]] Paint GetFill()const;
    
    [[nodiscard]] float GetKerning()const;
    void SetKerning(float value);
    [[nodiscard]] float GetLineSpacing()const;
    void SetLineSpacing(float value);
    
   
  
  };
}