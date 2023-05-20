#include "ChunkManager.hpp"

namespace Candy::Voxel {
    ChunkManager::ChunkManager(std::size_t size) : chunks(size)
    {
        CreateChunks();
    }

    void ChunkManager::CreateChunks(){
        for (int x=0; x<GetLengthInChunks(); x++)
        {
            for (int z=0; z<GetLengthInChunks(); z++)
            {
                for (int y=0; y<GetLengthInChunks(); y++)
                {
                    chunks[x, y, z] = new Chunk(*this, x, y, z);
                }
            }
        }
    }
    bool ChunkManager::HasChunk(std::size_t index) const {
        return chunks[index]!=nullptr;
    }
    /*bool ChunkManager::HasChunk(std::size_t xIndex, std::size_t yIndex) const {
        return chunks[xIndex, yIndex]!=nullptr;
    }*/
    bool ChunkManager::HasChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex) const {
        return chunks[xIndex, yIndex, zIndex]!=nullptr;
    }
    Chunk &ChunkManager::GetChunk(std::size_t index) {
        return *chunks[index];
    }
    const Chunk &ChunkManager::GetChunk(std::size_t index) const {
        return *chunks[index];
    }
    /*Chunk &ChunkManager::GetChunk(std::size_t xIndex, std::size_t yIndex) {
        return *chunks[xIndex, yIndex];
    }
    const Chunk &ChunkManager::GetChunk(std::size_t xIndex, std::size_t yIndex) const {
        return *chunks[xIndex, yIndex];
    }*/
    /*Chunk &ChunkManager::GetChunk(const Math::Vector2Int index) {
        return *chunks[index];
    }
    const Chunk &ChunkManager::GetChunk(const Math::Vector2Int index) const {
        return *chunks[index];
    }*/
    Chunk &ChunkManager::GetChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex) {
        return *chunks[xIndex, yIndex, zIndex];
    }
    const Chunk &ChunkManager::GetChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex) const {
        return *chunks[xIndex, yIndex, zIndex];
    }
    Chunk &ChunkManager::GetChunk(const Math::Vector3Int index) {
        return *chunks[index];
    }
    const Chunk &ChunkManager::GetChunk(const Math::Vector3Int index) const {
        return *chunks[index];
    }
    std::size_t ChunkManager::GetLengthInChunks()const{
        return chunks.Size();
    }
    std::size_t ChunkManager::GetTotalChunks()const{
        return chunks.SizeCubed();
    }
    bool ChunkManager::IsBorderChunk(const Chunk& chunk)const{
        return IsBorderChunk(chunk.GetCoord());
    }
    bool ChunkManager::IsBorderChunk(const Math::Vector3Int& chunkCoord)const{
        if (chunkCoord.x==0 || chunkCoord.y==0 || chunkCoord.z==0)
        {
            return true;
        }
        else{
            int size = chunks.Size()-1;
            return chunkCoord.x==size || chunkCoord.y==size || chunkCoord.z==size;
        }
    }




}