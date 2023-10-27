#pragma once
#include "Region.hpp"

namespace Candy::Gum
{
  class Root : public Region
  {
  
  public:
    Root();
  
  public:
    [[nodiscard]] bool Contains(Math::Vector2 localPoint) const override;
  };
  
  
}