#include <gum/base/Layout.hpp>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  void Layout::OnLayout()
  {
    //CANDY_CORE_INFO("Layout::OnLayout()");
    this->Region::OnLayout();
    //CANDY_CORE_INFO("Layout::Layout children");
    LayoutChildren();
  }
  
  float Layout::GetSpacing()const
  {
    return spacing;
  }
  void Layout::SetSpacing(float value)
  {
    spacing = value;
  }
  SizeGuide Layout::CalculateSizeGuide()const
  {
    SizeGuide result{};
    Math::Vector2 spaceVec{spacing, spacing};
    for (const SharedPtr<Node>& child : children)
    {
      result.min += child->GetMinSize() + spaceVec;
      result.pref += child->GetPrefSize() + spaceVec;
      result.max += child->GetMaxSize() + spaceVec;
    }
    return result;
  }
  
  
  
}