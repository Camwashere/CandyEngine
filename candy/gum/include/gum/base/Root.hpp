#pragma once
#include "Region.hpp"

namespace Candy::Gum
{
  class Root : public Node
  {
  protected:
    void CalculateBounds() override;
    void LayoutChildren() override;
    
  public:
    explicit Root(SceneGraph& sceneGraph);
  
  public:
    [[nodiscard]] bool Contains(Math::Vector2 localPoint) const override;
  };
  
  
}