#include "gum/GumGraph.hpp"
#include "CandyPch.hpp"
#include "gum/GumObject.hpp"
#include <gum/GumRenderer.hpp>
namespace Candy::Gum
{
  
  GumGraph::GumGraph(std::string_view graphName) : name(graphName)
  {
  }
  
  
  void GumGraph::Update()
  {
    // Loop while there are dirty objects in the queue
    while (!dirtyObjects.empty())
    {
      // Get the dirty object from the front of the queue
      const GumID id = dirtyObjects.front();
      dirtyObjects.pop();
      
      GumObject* object = objects[id].get();
      
      // Process the dirty object here
      if (object->HasDirtyFlag(GumObject::DirtyFlags::Transform))
      {
        object->CalculateTransformMatrices();
      }
      if (object->HasDirtyFlag(GumObject::DirtyFlags::DepthIndex))
      {
        object->CalculateDepthIndices();
      }
      if (object->HasDirtyFlag(GumObject::DirtyFlags::Shape))
      {
        object->CalculateLocalBounds();
      }
      
      // Store the parent's prior dirty flags to update children if necessary
      GumObject::DirtyFlags parentDirtyFlags = object->dirtyFlags;
      // Mark the object as clean
      object->MarkClean();
      
      // Enqueue the children if they are not already dirty
      for (GumID childId: object->childrenIDs)
      {
        if (objects[childId]->dirtyFlags == GumObject::DirtyFlags::None)
        {
          objects[childId]->AppendDirtyFlag(parentDirtyFlags);
          dirtyObjects.push(childId);
        }
      }
    }
    
    // Render the scene now that the object data has been updated
    Render();
  }
  
  void GumGraph::Render()
  {
    GumRenderer::BeginScene();
    
    for (const auto& object : objects)
    {
      if (object->IsVisible())
      {
        GumRenderer::SubmitShape(object->transform.worldMatrix, object->shape.get(), object->worldDepthIndex);
      }
      
    }
    
    GumRenderer::EndScene();
  }
  
  bool GumGraph::HasAvailableIDs() const
  {
    return !availableIDs.empty();
  }
  bool GumGraph::RemoveObject(GumID id)
  {
    if (id.IsNull())
    {
      return false;
    }
    else if (id == objects.LastID())
    {
      DetachObjectData(objects.Last());
      objects.PopBack();
    }
    else
    {
      DetachObjectData(objects[id]);
      availableIDs.push_back(id);
    }
    return true;
    
  }
  const GumObject* GumGraph::GetObject(GumID id)const
  {
    return objects[id].get();
  }
  
  GumObject* GumGraph::GetObject(GumID id)
  {
    return objects[id].get();
  }
  void GumGraph::DetachObjectData(const SharedPtr<GumObject>& object)
  {
    object->childrenIDs.clear();
    object->parentID = GumID::NULL_ID;
    object->graph = nullptr;
    object->id = GumID::NULL_ID;
  }
  
  GumID GumGraph::AddObject(const SharedPtr<GumObject>& object)
  {
    if (HasAvailableIDs())
    {
      GumID id = availableIDs.front();
      availableIDs.pop_front();
      objects[id] = object;
      return id;
    }
    else
    {
      objects.PushBack(object);
      return objects.LastID();
    }
  }
  
  bool GumGraph::IsIDAssigned(GumID id) const
  {
    if (id<objects.LastID() && id>=objects.FirstID())
    {
      return std::find(availableIDs.begin(), availableIDs.end(), id) == availableIDs.end();
    }
    return false;
  }
}