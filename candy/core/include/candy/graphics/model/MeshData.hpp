#pragma once
#include <candy/math/Vector.hpp>
#include <candy/graphics/Color.hpp>
#include <candy/base/Instrumentor.hpp>
namespace Candy::Graphics
{
  
  struct MeshVertexBasic
  {
    Math::Vector3 position;
  };
  struct MeshVertexColored
  {
    Math::Vector3 position;
    Color color;
    
    MeshVertexColored();
    MeshVertexColored(const MeshVertexColored& other);
    MeshVertexColored(const Math::Vector3& positionValue, const Color& colorValue);
    
    MeshVertexColored& operator=(const MeshVertexColored& other);
    bool operator==(const MeshVertexColored& other)const;
    bool operator!=(const MeshVertexColored& other)const;
    
    [[nodiscard]] std::string ToString()const;
  };
  struct MeshVertexTextured
  {
    Math::Vector3 position;
    Math::Vector2 uv;
  };
  struct MeshVertexNormalColored
  {
    Math::Vector3 position;
    Math::Vector3 normal;
    Color color;
  };
  
  struct MeshVertex
  {
    Math::Vector3 position;
    Color color;
    Math::Vector3 normal;
    Math::Vector2 uv;
    
    MeshVertex();
    MeshVertex(const MeshVertex& other);
    MeshVertex(const Math::Vector3& positionValue, const Color& colorValue, const Math::Vector3& normalValue, const Math::Vector2& uvValue);
    
    MeshVertex& operator=(const MeshVertex& other);
    bool operator==(const MeshVertex& other)const;
    bool operator!=(const MeshVertex& other)const;
    
    [[nodiscard]] std::string ToString()const;
    
  };
  
  
  template<class Vertex, typename Index=uint32_t>
  struct MeshData
  {
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    
    MeshData() : vertices{}, indices{}
    {
    
    }
    MeshData(const MeshData& other) : vertices(other.vertices), indices(other.indices)
    {
    
    }
    MeshData(const std::vector<Vertex>& verticesValue, const std::vector<Index>& indicesValue) : vertices(verticesValue), indices(indicesValue)
    {
    
    }
    
    MeshData& operator=(const MeshData& other)
    {
      CANDY_PROFILE_FUNCTION();
      vertices.resize(other.vertices.size());
      indices.resize(other.indices.size());
      for (int i=0; i<other.vertices.size(); i++)
      {
        vertices[i] = other.vertices[i];
      }
      for (int i=0; i<other.indices.size(); i++)
      {
        indices[i] = other.indices[i];
      }
      return *this;
    }
    bool operator==(const MeshData& other)const
    {
      CANDY_PROFILE_FUNCTION();
      if(vertices.size() != other.vertices.size() || indices.size() != other.indices.size())
      {
        return false;
      }
      for (int i=0; i<vertices.size(); i++)
      {
        if(vertices[i] != other.vertices[i])
        {
          CANDY_CORE_ERROR("Vert not equal: {0} != {1}", vertices[i].ToString(), other.vertices[i].ToString());
          return false;
        }
      }
      for (int i=0; i<indices.size(); i++)
      {
        if(indices[i] != other.indices[i])
        {
          CANDY_CORE_ERROR("Index not equal: {0} != {1}", indices[i], other.indices[i]);
          return false;
        }
      }
      return true;
    }
    bool operator!=(const MeshData& other)const
    {
      CANDY_PROFILE_FUNCTION();
      return !(*this == other);
    }
    
    
    [[nodiscard]] bool IsValid()const
    {
      CANDY_PROFILE_FUNCTION();
      if(indices.size() % 3 != 0)
      {
        return false;
      }
      
      return !(vertices.empty() || indices.empty());
      
    }
    [[nodiscard]] bool Empty()const
    {
      return vertices.empty() && indices.empty();
    }
    [[nodiscard]] size_t VertexCount()const
    {
      return vertices.size();
    }
    [[nodiscard]] size_t IndexCount()const
    {
      return indices.size();
    }
    
    [[nodiscard]] std::string ToString()const
    {
      CANDY_PROFILE_FUNCTION();
      std::string str;
      for (int i=0; i<vertices.size(); i++)
      {
        str += vertices[i].ToString() + "\n";
      }
      
      return str;
      
    }
    
    
  };
  
  
}