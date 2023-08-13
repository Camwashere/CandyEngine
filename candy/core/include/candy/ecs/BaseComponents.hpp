#pragma once
#include <candy/base/UUID.hpp>
#include <candy/math/Math.hpp>
//#include <Candy/Graphics.hpp>
#include <entt/entt.hpp>
#include <candy/graphics/model/Mesh.hpp>
#include <candy/graphics/material/Material.hpp>
namespace Candy::ECS
{
  struct IDComponent{
    UUID id;
  };
  
  struct TagComponent{
    std::string tag;
  };
  
  struct TransformComponent
  {
    //Math::Matrix4 matrix = Math::Matrix4::IDENTITY;

    Math::Vector3 position = {0.0f, 0.0f, 0.0f};
    Math::Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Math::Vector3 scale = {1.0f, 1.0f, 1.0f};
    
    
    [[nodiscard]] Math::Matrix4 GetMatrix()const
    {
      Math::Quaternion rot = Math::Quaternion::Euler(rotation);
      Math::Matrix4 matrix = Math::Matrix4::Translate(Math::Matrix4::IDENTITY, position) * Math::Matrix4::Rotate(Math::Matrix4::IDENTITY, rot) * Math::Matrix4::Scale(Math::Matrix4::IDENTITY, scale);
      //matrix[1,1]*=-1;
      return matrix;
    }
    
    
  };
  
  struct MeshComponent
  {
    Graphics::Mesh* mesh;
    //Graphics::Material material;
  };
  
  /*struct SpriteRendererComponent
  {
    Color color = Color::white;
    SharedPtr<Graphics::Texture> texture;
    float tilingFactor=1.0f;
    
    SpriteRendererComponent()=default;
    SpriteRendererComponent(const SpriteRendererComponent&)=default;
    explicit SpriteRendererComponent(const Color& colorValue) : color(colorValue){}
  };
  
  struct MeshFilterComponent
  {
    Graphics::Mesh mesh;
  };
  
  struct MeshRendererComponent
  {
    Graphics::Material material;
  };*/
  
  
  template<typename... Component>
  struct ComponentGroup
  {
  };
  
  using AllComponents =
  ComponentGroup<IDComponent, TagComponent, TransformComponent, MeshComponent>;
}