#include <candy/ecs/SceneSerializer.hpp>
#include <candy/ecs/Entity.hpp>
#include <utility>
#include <ryml_std.hpp>
#include <ryml.hpp>

#include <c4/format.hpp>
#include <candy/app/Application.hpp>
#include <candy/graphics/model/MeshData.hpp>


namespace Candy
{
  size_t to_chars(c4::substr buf, const Color& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{},{}]", v.x, v.y, v.z, v.w);
  }
  
  bool from_chars(c4::csubstr buf, Color* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    size_t ret = c4::unformat(buf, "[{},{},{},{}]", v->x, v->y, v->z, v->w);
    return ret != c4::csubstr::npos;
  }
}

namespace Candy::Math
{
  
  size_t to_chars(c4::substr buf, const Candy::Math::Vector4& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{},{}]", v.x, v.y, v.z, v.w);
  }
  
  bool from_chars(c4::csubstr buf, Candy::Math::Vector4* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    size_t ret = c4::unformat(buf, "[{},{},{},{}]", v->x, v->y, v->z, v->w);
    return ret != c4::csubstr::npos;
  }
  
  size_t to_chars(c4::substr buf, const Candy::Math::Quaternion& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{},{}]", v.x, v.y, v.z, v.w);
  }
  
  bool from_chars(c4::csubstr buf, Candy::Math::Quaternion* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    size_t ret = c4::unformat(buf, "[{},{},{},{}]", v->x, v->y, v->z, v->w);
    return ret != c4::csubstr::npos;
  }
  
  size_t to_chars(c4::substr buf, const Candy::Math::Vector3& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{},{}]", v.x, v.y, v.z);
  }
  
  bool from_chars(c4::csubstr buf, Candy::Math::Vector3* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    size_t ret = c4::unformat(buf, "[{},{},{}]", v->x, v->y, v->z);
    return ret != c4::csubstr::npos;
  }
  
  size_t to_chars(c4::substr buf, const Candy::Math::Vector2& v)
  {
    // this call to c4::format() is the type-safe equivalent
    // of snprintf(buf.str, buf.len, "(%f,%f,%f)", v.x, v.y, v.z)
    return c4::format(buf, "[{},{}]", v.x, v.y);
  }
  
  bool from_chars(c4::csubstr buf, Candy::Math::Vector2* v)
  {
    // equivalent to sscanf(buf.str, "(%f,%f,%f)", &v->x, &v->y, &v->z)
    // --- actually snscanf(buf.str, buf.len, ...) but there's
    // no such function in the standard.
    size_t ret = c4::unformat(buf, "[{},{}]", v->x, v->y);
    return ret != c4::csubstr::npos;
  }
  
}

namespace c4 {
  namespace yml {
    
    template<>
    void write(c4::yml::NodeRef* n, const Candy::Graphics::MeshVertex& vert)
    {
      *n |= c4::yml::MAP;
      (*n)["Position"] << vert.position;
      (*n)["Color"] << vert.color;
      (*n)["Normal"] << vert.normal;
      (*n)["UV"] << vert.uv;
    }
    
    template<>
    bool read(const c4::yml::ConstNodeRef& n, Candy::Graphics::MeshVertex *vec)
    {
      if (n.is_map())
      {
        n["Position"] >> vec->position;
        n["Color"] >> vec->color;
        n["Normal"] >> vec->normal;
        n["UV"] >> vec->uv;
        return true;
      }
      
      return false;
    }


    
    
  }
}

namespace Candy::ECS
{
  using namespace Math;
  using namespace Graphics;
  
  SceneSerializer::SceneSerializer(SharedPtr<Scene> scene) : scene(std::move(scene))
  {
  
  }
  
  static void SerializeEntity(c4::yml::NodeRef& entitiesNode, Entity entity)
  {
    CANDY_CORE_ASSERT(entity.HasComponent<IDComponent>(), "Entity does not have ID Component. Cannot Serialize");
    auto child = entitiesNode.append_child();
    child |= c4::yml::MAP;
    child["Entity"] << (uint64_t) entity.GetUUID();
    
    if (entity.HasComponent<TagComponent>())
    {
      auto tagNode = child["TagComponent"];
      tagNode |= c4::yml::MAP;
      tagNode["Tag"] << entity.GetTag();
    }
    
    if (entity.HasComponent<TransformComponent>())
    {
      auto transformNode = child["TransformComponent"];
      transformNode |= c4::yml::MAP;
      auto& transform = entity.GetComponent<TransformComponent>();
      transformNode["Position"] << transform.GetLocalPosition();
      transformNode["Rotation"] << transform.GetLocalRotation();
      transformNode["Scale"] << transform.GetLocalScale();
    }
    
    if (entity.HasComponent<MeshFilterComponent>())
    {
      auto meshNode = child["MeshFilterComponent"];
      meshNode |= c4::yml::MAP;
      auto& mesh = entity.GetComponent<MeshFilterComponent>();
      
      meshNode["Vertices"] << mesh.meshData.vertices;
      meshNode["Indices"] << mesh.meshData.indices;
    }
    
    if (entity.HasComponent<MeshRendererComponent>())
    {
      auto meshRendererNode = child["MeshRendererComponent"];
      meshRendererNode |= c4::yml::MAP;
      auto& meshRenderer = entity.GetComponent<MeshRendererComponent>();
      if (meshRenderer.texture)
      {
        meshRendererNode["Texture"] << meshRenderer.texture->GetPath().string();
      }
      else
      {
        meshRendererNode["Texture"] << "";
      }
    }
    if (entity.HasComponent<SpriteRendererComponent>())
    {
      auto spriteRendererNode = child["SpriteRendererComponent"];
      spriteRendererNode |= c4::yml::MAP;
      auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();
      if (spriteRenderer.texture)
      {
        spriteRendererNode["Texture"] << spriteRenderer.texture->GetPath().string();
      }
      else
      {
        spriteRendererNode["Texture"] << "";
      }
      spriteRendererNode["Color"] << spriteRenderer.color;
      spriteRendererNode["TilingFactor"] << spriteRenderer.tilingFactor;
    }
    if (entity.HasComponent<CircleRendererComponent>())
    {
      auto circleRendererNode = child["CircleRendererComponent"];
      circleRendererNode |= c4::yml::MAP;
      auto& circleRenderer = entity.GetComponent<CircleRendererComponent>();
      circleRendererNode["Color"] << circleRenderer.color;
      circleRendererNode["Thickness"] << circleRenderer.thickness;
      circleRendererNode["Fade"] << circleRenderer.fade;
    }
    if (entity.HasComponent<LineRendererComponent>())
    {
      auto lineRendererNode = child["LineRendererComponent"];
      lineRendererNode |= c4::yml::MAP;
      auto& lineRenderer = entity.GetComponent<LineRendererComponent>();
      lineRendererNode["Color"] << lineRenderer.color;
      lineRendererNode["Thickness"] << lineRenderer.thickness;
      lineRendererNode["Start"] << lineRenderer.start;
      lineRendererNode["End"] << lineRenderer.end;
    }
    
    if (entity.HasComponent<TextRendererComponent>())
    {
      auto textRendererNode = child["TextRendererComponent"];
      textRendererNode |= c4::yml::MAP;
      auto& textRenderer = entity.GetComponent<TextRendererComponent>();
      textRendererNode["Text"] << textRenderer.text;
      textRendererNode["Color"] << textRenderer.color;
      textRendererNode["Kerning"] << textRenderer.kerning;
      textRendererNode["LineSpacing"] << textRenderer.lineSpacing;
      
    }
    
    if (entity.HasChildren())
    {
      auto childrenNode = child["Children"];
      childrenNode |= c4::yml::SEQ;
      for (auto& c : entity.GetChildren().children)
      {
        CANDY_CORE_ASSERT(entity.HasScene());
        Entity childEntity{c, entity.GetScene()};
        SerializeEntity(childrenNode, childEntity);
      }
    }
    
    
    
    
    
  }
  
  bool SceneSerializer::Serialize(const std::filesystem::path& filepath)
  {
    c4::yml::Tree tree;
    c4::yml::NodeRef root = tree.rootref();
    
    root |= c4::yml::MAP;
    auto sceneNode = root["Scene"];
    sceneNode |= c4::yml::MAP;
    sceneNode["Name"] << scene->name;
    auto entitiesNode = sceneNode["Entities"];
    entitiesNode |= c4::yml::SEQ;
    std::vector<Entity> roots{};
    for (auto [entt] : scene->registry.storage<entt::entity>().each())
    {
      
      Entity entity{entt, scene.get()};
      if (entity.IsRoot())
      {
        roots.push_back(entity);
      }
      /*if (entity)
      {
        SerializeEntity(entitiesNode, entity);
      }*/
    }
    
    for (auto& r : roots)
    {
      SerializeEntity(entitiesNode, r);
    }
    
    FILE* out = fopen(filepath.string().c_str(), "w");
    if (!out)
    {
      CANDY_CORE_ERROR("Failed to open file {0} for project serialization", filepath.string());
      return false;
    }
    c4::yml::emit_yaml(tree, out);
    return true;
  }
  
  void DeserializeEntity(c4::yml::NodeRef& entityNode, Entity parentEntity, const SharedPtr<Scene>& scene)
  {
    std::uint64_t uuid;
    std::string tag;
    entityNode["Entity"] >> uuid;
    
    auto tagComponent = entityNode["TagComponent"];
    tagComponent["Tag"] >> tag;
    
    Entity deserializedEntity = scene->CreateEntityWithUUID(uuid, tag);
    
    if (parentEntity)
    {
      deserializedEntity.SetParent(parentEntity);
    }
    
    auto transformComponent = entityNode["TransformComponent"];
    if (transformComponent.has_key())
    {
      auto& tc = deserializedEntity.GetComponent<TransformComponent>();
      Math::Vector3 position;
      Math::Quaternion rotation;
      Math::Vector3 scale;
      
      transformComponent["Position"] >> position;
      transformComponent["Rotation"] >> rotation;
      transformComponent["Scale"] >> scale;
      tc.SetLocal(position, rotation, scale);
      
      /*if (parentEntity)
      {
        tc.SetParent(&parentEntity.GetComponent<TransformComponent>());
      }*/
      //tc.entity = deserializedEntity;
    }
    
    auto meshFilterComponent = entityNode["MeshFilterComponent"];
    if (meshFilterComponent.has_key())
    {
      MeshData meshData{};
      meshFilterComponent["Vertices"] >> meshData.vertices;
      meshFilterComponent["Indices"] >> meshData.indices;
      
      auto& meshComp = deserializedEntity.AddComponent<MeshFilterComponent>();
      meshComp.meshData = meshData;
      
    }
    
    auto meshRendererComponent = entityNode["MeshRendererComponent"];
    if (meshRendererComponent.has_key())
    {
      std::string texturePath;
      meshRendererComponent["Texture"] >> texturePath;
      if (!texturePath.empty())
      {
        auto& meshRendererComp = deserializedEntity.AddComponent<MeshRendererComponent>();
        meshRendererComp.texture = Texture::Create(texturePath);
      }
    }
    
    auto spriteRendererComponent = entityNode["SpriteRendererComponent"];
    if (spriteRendererComponent.has_key())
    {
      auto& spriteRendererComp = deserializedEntity.AddComponent<SpriteRendererComponent>();
      std::string texturePath;
      spriteRendererComponent["Texture"] >> texturePath;
      if (!texturePath.empty())
      {
        
        spriteRendererComp.texture = Texture::Create(texturePath);
      }
      spriteRendererComponent["Color"] >> spriteRendererComp.color;
      spriteRendererComponent["TilingFactor"] >> spriteRendererComp.tilingFactor;
    }
    
    auto circleRendererComponent = entityNode["CircleRendererComponent"];
    if (circleRendererComponent.has_key())
    {
      auto& circleRendererComp = deserializedEntity.AddComponent<CircleRendererComponent>();
      circleRendererComponent["Color"] >> circleRendererComp.color;
      circleRendererComponent["Thickness"] >> circleRendererComp.thickness;
      circleRendererComponent["Fade"] >> circleRendererComp.fade;
    }
    
    auto lineRendererComponent = entityNode["LineRendererComponent"];
    if (lineRendererComponent.has_key())
    {
      auto& lineRendererComp = deserializedEntity.AddComponent<LineRendererComponent>();
      lineRendererComponent["Color"] >> lineRendererComp.color;
      lineRendererComponent["Thickness"] >> lineRendererComp.thickness;
      lineRendererComponent["Start"] >> lineRendererComp.start;
      lineRendererComponent["End"] >> lineRendererComp.end;
    }
    
    auto textRendererComponent = entityNode["TextRendererComponent"];
    if (textRendererComponent.has_key())
    {
      auto& textRendererComp = deserializedEntity.AddComponent<TextRendererComponent>();
      textRendererComponent["Text"] >> textRendererComp.text;
      textRendererComponent["Color"] >> textRendererComp.color;
      textRendererComponent["Kerning"] >> textRendererComp.kerning;
      textRendererComponent["LineSpacing"] >> textRendererComp.lineSpacing;
      textRendererComp.font = Font::Default();
    }
    
    auto childrenNode = entityNode["Children"];
    if (childrenNode.has_key())
    {
      for (auto child : childrenNode)
      {
        DeserializeEntity(child, deserializedEntity, scene);
      }
    }
  }
  
  bool SceneSerializer::Deserialize(const std::filesystem::path& filepath)
  {
    std::ifstream fin(filepath);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string yaml_str = buffer.str();
    
    if (yaml_str.empty())
    {
      CANDY_CORE_ERROR("EMPTY YAML STRING WITH PATH: {}", filepath);
      return false;
    }
    
    ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(yaml_str));
    ryml::NodeRef root = tree.rootref();
    
    auto sceneNode = root["Scene"];
    if (sceneNode.empty())
    {
      CANDY_CORE_ERROR("EMPTY PROJECT NODE");
      return false;
    }
    auto nameNode = root["Name"];
    if (nameNode.has_key())
    {
      nameNode >> scene->name;
    }
   
    auto entitiesNode = sceneNode["Entities"];
   
    if (entitiesNode.empty())
    {
      return true;
    }
    
    for (auto entity : entitiesNode)
    {
      DeserializeEntity(entity, Entity(), scene);
      /*std::uint64_t uuid;
      std::string tag;
      entity["Entity"] >> uuid;
      
      auto tagComponent = entity["TagComponent"];
      tagComponent["Tag"] >> tag;
      
      Entity deserializedEntity = scene->CreateEntityWithUUID(uuid, tag);
      
      auto transformComponent = entity["TransformComponent"];
      if (transformComponent.has_key())
      {
        auto& tc = deserializedEntity.GetComponent<TransformComponent>();
        Math::Vector3 position;
        Math::Quaternion rotation;
        Math::Vector3 scale;
        transformComponent["Position"] >> position;
        transformComponent["Rotation"] >> rotation;
        transformComponent["Scale"] >> scale;
        tc.SetLocal(position, rotation, scale);
        tc.entity = deserializedEntity;
      }
      
      auto meshFilterComponent = entity["MeshFilterComponent"];
      if (meshFilterComponent.has_key())
      {
        MeshData meshData{};
        meshFilterComponent["Vertices"] >> meshData.vertices;
        meshFilterComponent["Indices"] >> meshData.indices;
        
        auto& meshComp = deserializedEntity.AddComponent<MeshFilterComponent>();
        meshComp.meshData = meshData;
        
      }
      
      auto meshRendererComponent = entity["MeshRendererComponent"];
      if (meshRendererComponent.has_key())
      {
        std::string texturePath;
        meshRendererComponent["Texture"] >> texturePath;
        if (!texturePath.empty())
        {
          auto& meshRendererComp = deserializedEntity.AddComponent<MeshRendererComponent>();
          meshRendererComp.texture = Texture::Create(texturePath);
        }
      }
      
      auto spriteRendererComponent = entity["SpriteRendererComponent"];
      if (spriteRendererComponent.has_key())
      {
        auto& spriteRendererComp = deserializedEntity.AddComponent<SpriteRendererComponent>();
        std::string texturePath;
        spriteRendererComponent["Texture"] >> texturePath;
        if (!texturePath.empty())
        {
          
          spriteRendererComp.texture = Texture::Create(texturePath);
        }
        spriteRendererComponent["Color"] >> spriteRendererComp.color;
        spriteRendererComponent["TilingFactor"] >> spriteRendererComp.tilingFactor;
      }
      
      auto circleRendererComponent = entity["CircleRendererComponent"];
      if (circleRendererComponent.has_key())
      {
        auto& circleRendererComp = deserializedEntity.AddComponent<CircleRendererComponent>();
        circleRendererComponent["Color"] >> circleRendererComp.color;
        circleRendererComponent["Thickness"] >> circleRendererComp.thickness;
        circleRendererComponent["Fade"] >> circleRendererComp.fade;
      }
      
      auto lineRendererComponent = entity["LineRendererComponent"];
      if (lineRendererComponent.has_key())
      {
        auto& lineRendererComp = deserializedEntity.AddComponent<LineRendererComponent>();
        lineRendererComponent["Color"] >> lineRendererComp.color;
        lineRendererComponent["Thickness"] >> lineRendererComp.thickness;
        lineRendererComponent["Start"] >> lineRendererComp.start;
        lineRendererComponent["End"] >> lineRendererComp.end;
      }
      
      auto textRendererComponent = entity["TextRendererComponent"];
      if (textRendererComponent.has_key())
      {
        auto& textRendererComp = deserializedEntity.AddComponent<TextRendererComponent>();
        textRendererComponent["Text"] >> textRendererComp.text;
        textRendererComponent["Color"] >> textRendererComp.color;
        textRendererComponent["Kerning"] >> textRendererComp.kerning;
        textRendererComponent["LineSpacing"] >> textRendererComp.lineSpacing;
        textRendererComp.font = Font::Default();
      }*/
      
      
    }
    return true;
  }
}


