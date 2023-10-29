#pragma once
#include <gum/base/Layout.hpp>

namespace Candy::Gum
{
  class BoxLayout : public Layout
  {
  public:
    enum class LayoutType
    {
      Horizontal,
      Vertical,
      Both,
    };
    
  private:
    LayoutType layoutType = LayoutType::Horizontal;
  protected:
    virtual void LayoutChildren()override;
    
  public:
    BoxLayout();
  };
}