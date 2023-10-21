#include <gum/base/Root.hpp>
#include "CandyPch.hpp"
namespace Candy::Gum
{
  Root::Root(SceneGraph& graph) : Node(graph)
  {
    CANDY_PROFILE_FUNCTION();
    //layoutTranslation = Math::Vector2(0, 0);
    position = Math::Vector2::zero;
    name = "Root";
    localTransform = Math::Matrix3::IDENTITY;
    localToParentTransform = Math::Matrix3::IDENTITY;
    localToRootTransform = Math::Matrix3::IDENTITY;
    
  }
  bool Root::Contains(Math::Vector2 scenePoint) const
  {
    CANDY_PROFILE_FUNCTION();
    return GetLocalBounds().Contains(scenePoint);
    //return (localBounds.Contains(scenePoint));
    
  }
  void Root::CalculateBounds()
  {
    CANDY_PROFILE_FUNCTION();
    
    boundsInParent.SetSize(size);
    boundsInScene.SetSize(size);
  }
  void Root::LayoutChildren()
  {
    CANDY_PROFILE_FUNCTION();
    for (auto& child : children)
    {
      LayoutGuide guide = child->GetLayoutGuide();
      //child->SetLayoutTranslation(guide.prefPosition);
      //child->SetLayoutTranslation({0, 0});
      //child->SetLayoutSize(guide.prefSize);
      //child->SetLayoutSize(layoutSize);
      
      child->Layout();
    }
  }
  
  
  
  
}