#include "Mesh.hpp"
#include "../../../include/Candy/Math.hpp"
namespace Candy{ namespace Graphics {
    using namespace Math;
    static const Vector3 voxelVerts[8] = {
            
            Vector3(0, 0, 0), // 0
            Vector3(0.5f, 0, 0), // 1
            Vector3(0.5f, 0.5f, 0), // 2
            Vector3(0, 0.5f, 0), // 3
            Vector3(0, 0, 0.5f), // 4
            Vector3(0.5f, 0, 0.5f), // 5
            Vector3(0.5f, 0.5f, 0.5f), // 6
            Vector3(0, 0.5f, 0.5f) // 7
        
    };
    static const uint voxelTris[6][4]= {
            
            // Back, Front, Top, Bottom, Left, Right
            
            // 0 1 2 2 1 3
            {0, 3, 1, 2}, // Back Face
            {5, 6, 4, 7}, // Front Face
            {3, 7, 2, 6}, // Top Face
            {1, 5, 0, 4}, // Bottom Face
            {4, 7, 0, 3}, // Left Face
            {1, 2, 5, 6} // Right Face
        
    };
    
    static const Vector3 voxelNormals[6]={
            Vector3::back,
            Vector3::forward,
            Vector3::up,
            Vector3::down,
            Vector3::left,
            Vector3::right
    };
    
    static const Vector2 voxelUvs[4]= {
            
            Vector2 (0.0f, 0.0f),
            Vector2 (0.0f, 1.0f),
            Vector2 (1.0f, 0.0f),
            Vector2 (1.0f, 1.0f)
    };
    
    
    static void MakeTriangles(std::vector<uint>* tris, uint* vertexIndex)
    {
        tris->push_back(*vertexIndex);
        tris->push_back(*vertexIndex + 1);
        tris->push_back(*vertexIndex + 2);
        tris->push_back(*vertexIndex + 2);
        tris->push_back(*vertexIndex + 1);
        tris->push_back(*vertexIndex + 3);
        *vertexIndex += 4;
    }
    
    Mesh Mesh::CreateCubeMesh()
    {
        uint vertexIndex=0;
        Mesh mesh;
        
        for (int p=0; p<6; p++)
        {
            mesh.AddVertex(voxelVerts [voxelTris [p][0]]);
            mesh.AddVertex(voxelVerts [voxelTris [p][1]]);
            mesh.AddVertex(voxelVerts [voxelTris [p][2]]);
            mesh.AddVertex(voxelVerts [voxelTris [p][3]]);
            
            mesh.AddNormal(voxelNormals[p]);
            mesh.AddNormal(voxelNormals[p]);
            mesh.AddNormal(voxelNormals[p]);
            mesh.AddNormal(voxelNormals[p]);
            
            MakeTriangles(&mesh.triangles, &vertexIndex);
            
            mesh.AddUV(Vector2 (0.0f, 0.0f));
            mesh.AddUV(Vector2 (0.0f, 1.0f));
            mesh.AddUV(Vector2 (1.0f, 0.0f));
            mesh.AddUV(Vector2 (1.0f, 1.0f));
        }
        return mesh;
    }
    
    void Mesh::AddVertex(const Math::Vector3 &vertex) {
        vertices.push_back(vertex);
    }
    
    void Mesh::AddUV(const Math::Vector2 &uv) {
        uvs.push_back(uv);
    }
    
    void Mesh::AddTriangle(uint triangle) {
        triangles.push_back(triangle);
        
    }
    void Mesh::AddNormal(const Math::Vector3& normal)
    {
        normals.push_back(normal);
    }
    
    void Mesh::SetVertices(const std::vector<Math::Vector3> &verts) {
        vertices=verts;
        
    }
    
    void Mesh::SetTriangles(const std::vector<uint> tris) {
        triangles = tris;
        
    }
    
    void Mesh::SetUVs(const std::vector<Math::Vector2> &uvCoords) {
        uvs=uvCoords;
    }
    
    float* Mesh::GetVertexArray()const
    {
        float* verts = new float[vertices.size()*3];
        for (int i=0; i<vertices.size(); i++)
        {
            int index=i*3;
            verts[index] = vertices[i].x;
            verts[index+1] = vertices[i].y;
            verts[index+2] = vertices[i].z;
        }
        return verts;
    }
    float* Mesh::GetUVArray()const
    {
        float* uv = new float[uvs.size()*2];
        for (int i=0; i<uvs.size(); i++)
        {
            int index=i*3;
            uv[index] = uvs[i].x;
            uv[index+1] = uvs[i].y;
            uv[index+2];
        }
        return uv;
        
    }
    
    float* Mesh::GetArray()const
    {
        float* verts = new float[vertices.size()*8];
        for (int i=0; i<vertices.size(); i++)
        {
            int index=i*8;
            verts[index] = vertices[i].x;
            verts[index+1] = vertices[i].y;
            verts[index+2] = vertices[i].z;
            verts[index+3] = normals[i].x;
            verts[index+4] = normals[i].y;
            verts[index+5] = normals[i].z;
            verts[index+6] = uvs[i].x;
            verts[index+7] = uvs[i].y;
        }
        return verts;
    }
    uint* Mesh::GetTriangleArray()const
    {
        uint* tris = new uint[triangles.size()];
        for (int i=0; i<triangles.size(); i++)
        {
            tris[i] = triangles[i];
        }
        return tris;
    }
    
    
    bool Mesh::IsMeshDataValid()const
    {
        if (vertices.empty())
        {
            return false;
        }
        if (! uvs.empty())
        {
            if (vertices.size() != uvs.size())
            {
                return false;
            }
        }
        if(triangles.size() % 3 == 0)
        {
            return true;
        }
        return false;
    }
}}