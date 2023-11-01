#pragma once
#include <gum/widget/AbstractButton.hpp>
namespace Candy::Gum
{
  class Button : public AbstractButton
  {
  protected:
    Paint hoveredFill=Color::blue;
    Paint normalFill=Color::brown;
    Paint pressedFill=Color::green;
    Paint disabledFill=Color::grey;
    
  private:
    void UpdateFill();
    
  protected:
    virtual void OnMouseEntered(MouseEnteredEvent& event) override;
    virtual void OnMouseExited(MouseExitedEvent& event) override;
    virtual void OnMousePressed(MousePressedEvent& event) override;
    virtual void OnMouseReleased(MouseReleasedEvent& event) override;
    
  public:
    Button();
    
  public:
    void SetHoveredFill(const Paint& color);
    void SetNormalFill(const Paint& color);
    void SetPressedFill(const Paint& color);
    void SetDisabledFill(const Paint& color);
    
    [[nodiscard]] const Paint& GetHoveredFill() const;
    [[nodiscard]] const Paint& GetNormalFill() const;
    [[nodiscard]] const Paint& GetPressedFill() const;
    [[nodiscard]] const Paint& GetDisabledFill() const;
    
    
  
    
  
  };
}