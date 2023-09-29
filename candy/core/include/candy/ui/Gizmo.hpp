#pragma once
#include <candy/base/Base.hpp>
#include <candy/math/Matrix.hpp>
#include <candy/math/Quaternion.hpp>
#include <candy/ecs/TransformComponent.hpp>
#include <candy/graphics/model/MeshData.hpp>
namespace Candy
{
  
  struct GizmoTranslationMeshSettings
  {
    Color color;
    int resolution=8;
    float radius=0.05f;
    float height=1.0f;
    float arrowHeight=0.2f;
    float arrowRadius=0.1f;
  };
  
  struct GizmoMeshSettings
  {
    GizmoTranslationMeshSettings translation;
  };
  class Gizmo
  {
  public:
    enum class Type
    {
      NONE = BIT(0),
      TRANSLATE = BIT(1),
      ROTATE = BIT(2),
      SCALE = BIT(3),
      
    };
    
    enum class GizmoAxis
    {
      NONE = BIT(0),
      X = BIT(1),
      Y = BIT(2),
      Z = BIT(3),
      XY = X | Y,
      YZ = Y | Z,
      ZX = X | Z,
      ALL = X | Y | Z,
    };
    
  private:
    ECS::TransformComponent* target=nullptr;
    Math::Vector3 position;
    Math::Quaternion rotation;
    Math::Vector3 scale;
    float sensitivity=1.0f;
    bool visible=false;
    
    GizmoMeshSettings meshSettings;
    
    
    
    Graphics::MeshData<Graphics::MeshVertex> translationMesh;
    Graphics::MeshData<Graphics::MeshVertex> rotationMesh;
    Graphics::MeshData<Graphics::MeshVertex> scaleMesh;
    
  public:
    Gizmo();
    
  public:
    void SetTarget(ECS::TransformComponent* target);
    int GetTargetEntity()const;
    
    [[nodiscard]] const Graphics::MeshData<Graphics::MeshVertex>& GetTranslationMesh()const;
  };
}


