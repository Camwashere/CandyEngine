#pragma once
#include "GumTypes.hpp"
#include "GumGraph.hpp"
#include "candy/base/Instrumentor.hpp"
#include "candy/base/Assert.hpp"
#include "GumTransform.hpp"
#include <candy/math/geometry/Bounds2D.hpp>
#include <gum/shape/GumShape.hpp>
namespace Candy::Gum
{
  
  
  
  class GumObject
  {
    enum class DirtyFlags : uint16_t
    {
      None=BIT(0),
      Transform=BIT(1),
      DepthIndex=BIT(2),
      Shape=BIT(3),
      
      Queued=BIT(4),
    };
  private:
    GumID id;
    GumGraph* graph;
    GumID parentID;
    std::vector<GumID> childrenIDs;
    DirtyFlags dirtyFlags=DirtyFlags::None;
    
    
  protected:
    int localDepthIndex=0;
    int worldDepthIndex=0;
    GumTransform transform;
    Math::Bounds2D worldBounds;
    SharedPtr<GumShape> shape=nullptr;
    bool visible=false;
    
  public:
    explicit GumObject(GumGraph* gumGraph);
    
  private:
    void MarkDirty(DirtyFlags flag);
    void MarkClean();
    void AppendDirtyFlag(DirtyFlags flag);
    void RemoveDirtyFlag(DirtyFlags flag);
    [[nodiscard]] bool HasDirtyFlag(DirtyFlags flag)const;
    
    void CalculateTransformMatrices();
    void CalculateDepthIndices();
    void CalculateLocalBounds();
    
    
    
    
  public:
    operator bool()const;
    operator GumID()const;
    
    bool operator==(const GumObject& other)const;
    bool operator!=(const GumObject& other)const;
    
  public:
    // Transform
    void SetLocalPosition(const Math::Vector2& position);
    void SetLocalRotation(float rotation);
    void SetLocalScale(const Math::Vector2& scale);
    void SetLocalTransform(const Math::Vector2& position, float rotation, const Math::Vector2& scale);
    void SetLocalDepthIndex(int depthIndex);
    
    [[nodiscard]] const GumTransform& GetTransform()const;
    
    
    
    void SetVisible(bool value);
    
    void SetShape(const SharedPtr<GumShape>& gumShape);
    [[nodiscard]] GumID GetID()const;
    [[nodiscard]] GumID GetParentID()const;
    [[nodiscard]] bool Contains(const Math::Vector2& point)const;
    [[nodiscard]] const GumObject* GetParent()const;
    GumObject* GetParent();
    [[nodiscard]] const GumGraph* GetGraph()const;
    GumGraph* GetGraph();
    
    
    
    [[nodiscard]] bool HasParent()const;
    [[nodiscard]] const Math::Bounds2D& GetWorldBounds()const;
    [[nodiscard]] const Math::Bounds2D& GetLocalBounds()const;
    
    [[nodiscard]] GumID GetChildID(size_t index) const;
    [[nodiscard]] const std::vector<GumID>& GetChildrenIDs() const;
    std::vector<GumID>& GetChildrenIDs();
    [[nodiscard]] const GumObject* GetChild(size_t index) const;
    GumObject* GetChild(size_t index);
    std::vector<GumObject*> GetChildren();
    [[nodiscard]] std::vector<const GumObject*> GetChildren() const;
    [[nodiscard]] bool HasChildren() const;
    [[nodiscard]] size_t GetChildCount() const;
    [[nodiscard]] const GumShape* GetShape()const;
    GumShape* GetShape();
    bool IsVisible()const;
    
    friend class GumGraph;
    
  };
  
 
  
  
}