#pragma once
#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <Candy/CandyEngineBase.hpp>
#include "../../../include/Candy/Math.hpp"
namespace Candy::Graphics {
    class Mesh
    {
    public:
        static Mesh CreateCubeMesh();
    public:
        std::vector<Math::Vector3> vertices{};
        std::vector<Math::Vector2> uvs{};
        std::vector<uint> triangles{};
        std::vector<Math::Vector3> normals{};
    
    public:
        Mesh()=default;
        Mesh(const Mesh& other):vertices(other.vertices), uvs(other.uvs), triangles(other.triangles), normals(other.normals){}
    
    
    public:
        void AddVertex(const Math::Vector3& vertex);
        void AddUV(const Math::Vector2& uv);
        void AddTriangle(uint triangle);
        void AddNormal(const Math::Vector3& normal);
        
        
        void SetVertices(const std::vector<Math::Vector3>& verts);
        void SetTriangles(const std::vector<uint> tris);
        void SetUVs(const std::vector<Math::Vector2>& uvCoords);
        void SetNormals(const std::vector<Math::Vector3>& vertexNormals);
        
        float* GetVertexArray()const;
        Math::Vector3* GetVertArray(){return &vertices[0];}
        uint* GetTriangleArray()const;
        float* GetUVArray()const;
        Math::Vector3* GetNormalsArray(){return &normals[0];}
        float* GetArray()const;
        std::size_t GetVertexArraySize()const{return vertices.size()*3*sizeof(float);}
        std::size_t GetTriangleArraySize()const{return triangles.size()*sizeof(uint);}
        std::size_t GetUVArraySize()const{return uvs.size()*2*sizeof(float);}
        std::size_t GetNormalArraySize()const{return normals.size()*3*sizeof(float);}
        std::size_t GetArraySize()const{return vertices.size()*8*sizeof(float);}
        
        bool IsMeshDataValid()const;
        
        
    };
}

#endif //ENGINE_MESH_H
