#pragma once

#include <Candy/CandyEngine.hpp>

class ChunkRenderer
{
private:
    Candy::Noise::PerlinNoise noise;
    Candy::Voxel::ChunkManager manager;
    Candy::Graphics::Mesh mesh;

private:
    void RegisterBlocks();
    void InitBlocks();
    
    void AddFaces(const Candy::Voxel::Chunk& chunk, const Candy::Math::Vector3& position, int* vertexIndex);
    void AddVertices(int faceIndex, const Candy::Math::Vector3& position);
    void AddNormals(int faceIndex);
    void AddTriangles(int* vertexIndex);
    void AddUVs();
    
    void GenerateMesh(const Candy::Voxel::Chunk& chunk);

public:
    ChunkRenderer();

public:
    const Candy::Graphics::Mesh& ToMesh();
};

