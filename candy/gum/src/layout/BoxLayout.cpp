#include <gum/layout/BoxLayout.hpp>
#include <CandyPch.hpp>
namespace Candy::Gum
{
  using namespace Math;
  
  void BoxLayout::LayoutChildren()
  {
    //CANDY_CORE_CRITICAL("LAYING OUT CHILDREN IN BOX LAYOUT");
    Vector2 currentSize = Vector2::zero;
    Vector2 currentPosition = Vector2::zero;
    
    float xPosition = 0;
    
    //currentSize.height = maxHeight;
    
    SizeGuide sizeGuide = CalculateSizeGuide();
    
    if (sizeGuide.min.width > GetMinSize().width)
    {
    
    }
    if (sizeGuide.pref.width > GetPrefSize().width)
    {
    
    }
    if (sizeGuide.max.width > GetMaxSize().width)
    {
    
    }
    
    // If total width of preferred sizes exceeds the max width, calculate a reduction factor
    Vector2 reductionFactor{1, 1};
    if (sizeGuide.pref.width > GetMaxSize().width)
    {
      reductionFactor.width = GetMaxSize().width / sizeGuide.pref.width;
    }
    
    if (sizeGuide.pref.height > GetMaxSize().height)
    {
      reductionFactor.height = GetMaxSize().height / sizeGuide.pref.height;
    }
    
    Vector2 scaleUpFactor{1, 1}; // A factor to scale up the size of the children
    
    // If total preferred size is less than min size of the Box, calculate a scale-up factor
    if(sizeGuide.pref.width < GetMinSize().width)
    {
      scaleUpFactor.width = GetMinSize().width / sizeGuide.pref.width;
    }
    
    if(sizeGuide.pref.height < GetMinSize().height)
    {
      scaleUpFactor.height = GetMinSize().height / sizeGuide.pref.height;
    }
    
    Vector2 adjustmentFactor = Vector2::Max(reductionFactor, scaleUpFactor);
    
    float maxHeight = 0;
    for (const SharedPtr<Node>& child : children)
    {
      // Calculate the preferred size with the adjustment factor
      float prefWidth = child->GetPrefSize().width * adjustmentFactor.width;
      
      
      // Try to give the child its reduced preferred size, or as large as possible within its min-max range
      currentSize.width = Math::Clamp(prefWidth, child->GetMinSize().width, child->GetMaxSize().width);
      currentSize.height = Math::Clamp(GetPrefSize().height, child->GetMinSize().height, child->GetMaxSize().height);
      maxHeight = Math::Max(maxHeight, currentSize.height);
      child->SetSize(currentSize);
      // Set the child's position
      child->SetLayoutPosition(Vector2(xPosition, 0));
      
      // Increase the xPosition by the child's width
      xPosition += currentSize.width+spacing;
    }
    
    SetSize({xPosition, maxHeight});
  }
}