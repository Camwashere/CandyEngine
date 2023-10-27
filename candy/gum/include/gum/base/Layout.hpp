#pragma once
#include <candy/math/Vector.hpp>
#include <gum/base/Region.hpp>
namespace Candy::Gum
{
  struct SizeGuide
  {
    Math::Vector2 min;
    Math::Vector2 pref;
    Math::Vector2 max;
  };
  class Layout : public Region
  {
  protected:
    float spacing=0.0f;
    
    
  protected:
    virtual void OnLayout() override;
    virtual void LayoutChildren()=0;
    
  public:
    float GetSpacing()const;
    void SetSpacing(float value);
    SizeGuide CalculateSizeGuide()const;
    
  
  
  };
}