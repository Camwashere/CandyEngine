#pragma once
#include <candy/base/UUID.hpp>
#include <candy/math/Math.hpp>
//#include <Candy/Graphics.hpp>
#include <entt/entt.hpp>
#include <candy/graphics/model/Mesh.hpp>
#include <candy/graphics/material/Material.hpp>
#include <candy/graphics/font/Font.hpp>
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
      return matrix;
    }
    
    
  };
  
  
  
  struct MeshFilterComponent
  {
    Graphics::Mesh mesh;
    
    
    //MeshFilterComponent(const Graphics::Mesh& meshValue) : mesh(meshValue){}
  };
  
  struct MeshRendererComponent
  {
    SharedPtr<Graphics::Texture> texture;
  };
  
  struct SpriteRendererComponent
  {
    Color color = Color::white;
    SharedPtr<Graphics::Texture> texture;
    float tilingFactor=1.0f;
    
    SpriteRendererComponent()=default;
    SpriteRendererComponent(const SpriteRendererComponent&)=default;
    explicit SpriteRendererComponent(const Color& colorValue) : color(colorValue){}
    explicit SpriteRendererComponent(const SharedPtr<Graphics::Texture>& textureValue) : texture(textureValue){}
    SpriteRendererComponent(const SharedPtr<Graphics::Texture>& textureValue, const Color& colorValue) : color(colorValue), texture(textureValue){}
  };
  
  
  struct CircleRendererComponent
  {
    Color color = Color::white;
    float thickness = 1.0f;
    float fade = 0.005f;
    
    CircleRendererComponent()=default;
    CircleRendererComponent(const CircleRendererComponent&)=default;
  };
  
  struct LineRendererComponent
  {
    Color color = Color::white;
    float thickness = 1.0f;
    Math::Vector3 start = Math::Vector3::zero;
    Math::Vector3 end = Math::Vector3::zero;
    
  };
  
  
  struct TextRendererComponent
  {
    std::string text;
    SharedPtr<Graphics::Font> font=nullptr;
    Color color = Color::white;
    float kerning = 0.0f;
    float lineSpacing = 0.0f;
  };
  
  
  
  template<typename... Component>
  struct ComponentGroup
  {
  };
  
  using AllComponents =
  ComponentGroup<IDComponent, TagComponent, TransformComponent, SpriteRendererComponent, CircleRendererComponent, LineRendererComponent, TextRendererComponent, MeshFilterComponent, MeshRendererComponent>;
}