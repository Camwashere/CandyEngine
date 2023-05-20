#pragma once
#include "Chunk.hpp"
namespace Candy::Voxel {

    class ChunkManager
    {
    private:
        Collections::HeapArray3D<Chunk*> chunks;
    public:
        ChunkManager(std::size_t sizeInChunks);

    public:
        void CreateChunks();

    public:
        bool HasChunk(std::size_t index)const;
        bool HasChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const;

        Chunk& GetChunk(std::size_t index);
        const Chunk& GetChunk(std::size_t index)const;
        Chunk& GetChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex);
        const Chunk& GetChunk(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const;
        Chunk& GetChunk(const Math::Vector3Int index);
        const Chunk& GetChunk(const Math::Vector3Int index)const;

        std::size_t GetLengthInChunks()const;
        std::size_t GetTotalChunks()const;

    public:
        bool IsBorderChunk(const Chunk& chunk)const;
        bool IsBorderChunk(const Math::Vector3Int& chunkCoord)const;




    };
}
