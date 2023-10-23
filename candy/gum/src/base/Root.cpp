#include <gum/base/Root.hpp>
#include "CandyPch.hpp"
#include <gum/base/SceneGraph.hpp>
namespace Candy::Gum
{
  Root::Root(SceneGraph& graph) : Node(graph)
  {
    CANDY_PROFILE_FUNCTION();
    name = "Root";
    transform = Math::Matrix3::IDENTITY;
    SetLayoutPosition({0, 0});
    //boundsInParent.SetPosition({0, 0});
    //boundsInScene.SetPosition({0, 0});
    
  }
  bool Root::Contains(Math::Vector2 scenePoint) const
  {
    CANDY_PROFILE_FUNCTION();
    return GetBoundsInScene().Contains(scenePoint);
    
  }
  /*void Root::CalculateBounds()
  {
    CANDY_PROFILE_FUNCTION();
    SetSize(sceneGraph->GetSceneSize());
  }*/
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