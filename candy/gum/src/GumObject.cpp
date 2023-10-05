#include "gum/GumObject.hpp"
#include "CandyPch.hpp"

namespace Candy::Gum
{
  using namespace Math;
  GumObject::GumObject(GumGraph* gumGraph) : graph(gumGraph)
  {
  }
  
  
  
  GumObject::operator bool() const
  {
    return id.IsValid();
  }
  
  GumObject::operator GumID() const
  {
    return id;
  }
  
  bool GumObject::operator==(const GumObject& other) const
  {
    return id==other.id;
  }
  
  bool GumObject::operator!=(const GumObject& other) const
  {
    return id!=other.id;
  }
  void GumObject::SetVisible(bool value)
  {
    visible = value;
  }
  void GumObject::SetShape(const SharedPtr<GumShape>& gumShape)
  {
    shape = gumShape;
    MarkDirty(DirtyFlags::Shape);
  }
  GumID GumObject::GetID() const
  {
    return id;
  }
  
  GumID GumObject::GetParentID() const
  {
    return parentID;
  }
  
  
  bool GumObject::Contains(const Math::Vector2& point) const
  {
    if (worldBounds.Contains(point))
    {
    
    }
    return false;
  }
  const GumObject* GumObject::GetParent() const
  {
    return graph->GetObject(parentID);
  
  }
  
  GumObject* GumObject::GetParent()
  {
    return graph->GetObject(parentID);
    
  }
  
  
  void GumObject::SetLocalPosition(const Math::Vector2& position)
  {
    transform.localPosition = position;
    MarkDirty(DirtyFlags::Transform);
  }
  void GumObject::SetLocalRotation(float rotation)
  {
    transform.localRotation = rotation;
    MarkDirty(DirtyFlags::Transform);
  }
  void GumObject::SetLocalScale(const Math::Vector2& scale)
  {
    transform.localScale = scale;
    MarkDirty(DirtyFlags::Transform);
  }
  void GumObject::SetLocalTransform(const Math::Vector2& position, float rotation, const Math::Vector2& scale)
  {
    transform.localPosition = position;
    transform.localRotation = rotation;
    transform.localScale = scale;
    MarkDirty(DirtyFlags::Transform);
  }
  void GumObject::SetLocalDepthIndex(int depthIndex)
  {
    localDepthIndex = depthIndex;
    MarkDirty(DirtyFlags::DepthIndex);
  }
  
  const GumTransform& GumObject::GetTransform() const
  {
    return transform;
  }
  
  
  
  const GumGraph* GumObject::GetGraph() const
  {
    return graph;
  }
  
  GumGraph* GumObject::GetGraph()
  {
    return graph;
  }
  
  
  
  bool GumObject::HasParent() const
  {
    return parentID.IsValid();
  }
  
  
  const Math::Bounds2D& GumObject::GetWorldBounds() const
  {
    return worldBounds;
  }
  const Math::Bounds2D& GumObject::GetLocalBounds() const
  {
    CANDY_CORE_ASSERT(shape, "GumObject::GetLocalBounds() shape is null!");
    return shape->GetBoundingBox();
  }
  
  bool GumObject::HasChildren() const
  {
    return !childrenIDs.empty();
  }
  
  size_t GumObject::GetChildCount() const
  {
    return childrenIDs.size();
  }
  
  const GumShape* GumObject::GetShape() const
  {
    CANDY_CORE_ASSERT(shape, "GumObject::GetShape() shape is null!");
    return shape.get();
  }
  
  GumShape* GumObject::GetShape()
  {
    CANDY_CORE_ASSERT(shape, "GumObject::GetShape() shape is null!");
    return shape.get();
  }
  const GumObject* GumObject::GetChild(size_t index) const
  {
    CANDY_CORE_ASSERT(index<childrenIDs.size(), "GumObject::GetChild() index out of bounds");
    return graph->GetObject(childrenIDs[index]);
  }
  
  GumObject* GumObject::GetChild(size_t index)
  {
    CANDY_CORE_ASSERT(index<childrenIDs.size(), "GumObject::GetChild() index out of bounds");
    return graph->GetObject(childrenIDs[index]);
  }
  
  std::vector<GumObject*> GumObject::GetChildren()
  {
    std::vector<GumObject*> children(childrenIDs.size());
    for (size_t i = 0; i < childrenIDs.size(); i++)
    {
      children[i] = graph->GetObject(childrenIDs[i]);
      CANDY_CORE_ASSERT(children[i], "GumObject::GetChildren() Children vector contains null object!");
    }
    return children;
  }
  
  std::vector<const GumObject*> GumObject::GetChildren() const
  {
    std::vector<const GumObject*> children(childrenIDs.size());
    for (size_t i = 0; i<childrenIDs.size(); i++)
    {
      children[i] = graph->GetObject(childrenIDs[i]);
      CANDY_CORE_ASSERT(children[i], "GumObject::GetChildren() Children vector contains null object!");
    }
    return children;
  }
  
  GumID GumObject::GetChildID(size_t index) const
  {
    CANDY_CORE_ASSERT(index<childrenIDs.size(), "GumObject::GetChildID() index out of bounds");
    return childrenIDs[index];
  }
  
  const std::vector<GumID>& GumObject::GetChildrenIDs() const
  {
    return childrenIDs;
  }
  
  std::vector<GumID>& GumObject::GetChildrenIDs()
  {
    return childrenIDs;
  }
  
  bool GumObject::IsVisible() const
  {
    return visible;
  }
  
  
  
  void GumObject::MarkDirty(DirtyFlags flag)
  {
    AppendDirtyFlag(flag);
    if (!HasDirtyFlag(DirtyFlags::Queued))
    {
      graph->dirtyObjects.push(id);
      AppendDirtyFlag(DirtyFlags::Queued);
    }
  }
  void GumObject::AppendDirtyFlag(DirtyFlags flag)
  {
    
    dirtyFlags = static_cast<DirtyFlags>(static_cast<uint16_t>(dirtyFlags) | static_cast<uint16_t>(flag));
    
    
  }
  void GumObject::RemoveDirtyFlag(DirtyFlags flag)
  {
    dirtyFlags = static_cast<DirtyFlags>(static_cast<uint16_t>(dirtyFlags) & ~static_cast<uint16_t>(flag));
  }
  bool GumObject::HasDirtyFlag(DirtyFlags flag) const
  {
    return (static_cast<uint16_t>(dirtyFlags) & static_cast<uint16_t>(flag)) != 0;
  }
  void GumObject::MarkClean()
  {
    dirtyFlags = DirtyFlags::None;
  }
  
  void GumObject::CalculateTransformMatrices()
  {
    transform.localMatrix = Matrix3::Translate(Matrix3::IDENTITY, transform.localPosition)*Matrix3::Rotate(Matrix3::IDENTITY, transform.localRotation)*Matrix3::Scale(Matrix3::IDENTITY, transform.localScale);
    if (HasParent())
    {
      transform.worldMatrix = GetParent()->GetTransform().worldMatrix*transform.localMatrix;
    }
    else
    {
      transform.worldMatrix = transform.localMatrix;
    }
    
  }
  void GumObject::CalculateDepthIndices()
  {
    if (HasParent())
    {
      worldDepthIndex = GetParent()->worldDepthIndex + localDepthIndex;
    }
    else
    {
      worldDepthIndex = localDepthIndex;
    }
  }
  
  void GumObject::CalculateLocalBounds()
  {
    CANDY_CORE_ASSERT(shape);
    shape->ReCalculateBoundingBox();
    worldBounds = shape->GetBoundingBox();
  }
}