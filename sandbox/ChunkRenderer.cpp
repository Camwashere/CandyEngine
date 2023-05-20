#include "ChunkRenderer.hpp"
using namespace Candy;
using namespace Candy::Graphics;
using namespace Candy::Voxel;
ChunkRenderer::ChunkRenderer() : noise(2), manager(5)
{
    RegisterBlocks();
    InitBlocks();
    
}

void ChunkRenderer::RegisterBlocks()
{
    BlockType air("Air", 0);
    BlockType dirt("Dirt", 1);
    BlockType grass("Grass", 2);
    BlockTypeManager::Instance()->RegisterBlockType(air);
    BlockTypeManager::Instance()->RegisterBlockType(dirt);
    BlockTypeManager::Instance()->RegisterBlockType(grass);
}
void ChunkRenderer::InitBlocks()
{
    for (int z=0; z<manager.GetChunk(0).Size(); z++)
    {
        for (int x=0; x<manager.GetChunk(0).Size(); x++)
        {
            float noiseValue = noise.Evaluate(x+.5f, z+.5f);
            int height = Math::RoundToInt(noiseValue*manager.GetLengthInChunks());
            for (int y=0; y<height; y++)
            {
                manager.GetChunk(0).SetBlock(x, y, z, 1);
            }
        }
    }
}

void ChunkRenderer::AddFaces(const Candy::Voxel::Chunk& chunk, const Candy::Math::Vector3& position, int* vertexIndex)
{
    if (!chunk.BlockHasNeighborLeft(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::LeftFace, position);
        AddNormals(VoxelData::LeftFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
    if (!chunk.BlockHasNeighborRight(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::RightFace, position);
        AddNormals(VoxelData::RightFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
    if (!chunk.BlockHasNeighborTop(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::TopFace, position);
        AddNormals(VoxelData::TopFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
    if (!chunk.BlockHasNeighborBottom(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::BottomFace, position);
        AddNormals(VoxelData::BottomFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
    if (!chunk.BlockHasNeighborFront(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::FrontFace, position);
        AddNormals(VoxelData::FrontFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
    if (!chunk.BlockHasNeighborBack(position.x, position.y, position.z))
    {
        AddVertices(VoxelData::BackFace, position);
        AddNormals(VoxelData::BackFace);
        AddTriangles(vertexIndex);
        AddUVs();
    }
}

void ChunkRenderer::AddVertices(int faceIndex, const Math::Vector3& position)
{
    mesh.AddVertex(position + VoxelData::voxelVerts[VoxelData::voxelTris[faceIndex][0]]);
    mesh.AddVertex(position + VoxelData::voxelVerts[VoxelData::voxelTris[faceIndex][1]]);
    mesh.AddVertex(position + VoxelData::voxelVerts[VoxelData::voxelTris[faceIndex][2]]);
    mesh.AddVertex(position + VoxelData::voxelVerts[VoxelData::voxelTris[faceIndex][3]]);
}
void ChunkRenderer::AddNormals(int faceIndex)
{
    mesh.AddNormal(VoxelData::voxelNormals[faceIndex]);
    mesh.AddNormal(VoxelData::voxelNormals[faceIndex]);
    mesh.AddNormal(VoxelData::voxelNormals[faceIndex]);
    mesh.AddNormal(VoxelData::voxelNormals[faceIndex]);
}
void ChunkRenderer::AddTriangles(int* vertexIndex)
{
    mesh.triangles.push_back(*vertexIndex);
    mesh.triangles.push_back(*vertexIndex + 1);
    mesh.triangles.push_back(*vertexIndex + 2);
    mesh.triangles.push_back(*vertexIndex + 2);
    mesh.triangles.push_back(*vertexIndex + 1);
    mesh.triangles.push_back(*vertexIndex + 3);
    *vertexIndex += 4;
}
void ChunkRenderer::AddUVs()
{
    mesh.AddUV(Math::Vector2 (0.0f, 0.0f));
    mesh.AddUV(Math::Vector2 (0.0f, 1.0f));
    mesh.AddUV(Math::Vector2 (1.0f, 0.0f));
    mesh.AddUV(Math::Vector2 (1.0f, 1.0f));
}
void ChunkRenderer::GenerateMesh(const Chunk& chunk)
{
    int vertexIndex=0;
    for (int z=0; z<chunk.Size(); z++)
    {
        for (int x=0; x<chunk.Size(); x++)
        {
            for (int y=0; y<chunk.Size(); y++)
            {
                if (chunk.HasBlock(x, y, z))
                {
                    Math::Vector3 position(x, y, z);
                    AddFaces(chunk, position, &vertexIndex);
                }
            }
        }
    }
}
const Mesh& ChunkRenderer::ToMesh(){
    GenerateMesh(manager.GetChunk(0));
    return mesh;
    
    
}