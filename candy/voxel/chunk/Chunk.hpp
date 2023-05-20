#pragma once
#include "../block/Block.hpp"
namespace Candy::Voxel {
    class ChunkManager;

    template<std::size_t CHUNK_SIZE, std::size_t CHUNK_SIZE_SQUARED=CHUNK_SIZE*CHUNK_SIZE, std::size_t CHUNK_SIZE_CUBED=CHUNK_SIZE_SQUARED*CHUNK_SIZE>
    class ChunkBase
    {
    protected:
        const Math::Vector3Int coord;
        Collections::Array3D<Block, CHUNK_SIZE> blocks;

    public:
        ChunkBase(const Math::Vector3Int& chunkCoord) : coord(chunkCoord){}

    public:
        inline constexpr std::size_t Size()const{return CHUNK_SIZE;}
        inline constexpr std::size_t SizeSquared()const{return CHUNK_SIZE_SQUARED;}
        inline constexpr std::size_t SizeCubed()const{return CHUNK_SIZE_CUBED;}
        inline constexpr Math::Vector3Int GetCoord()const{return coord;}

        inline constexpr void SetBlock(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex, Block block){blocks[xIndex, yIndex, zIndex]=block;}
        inline constexpr void SetBlock(const Math::Vector3Int& index, Block block){blocks[index.x, index.y, index.z]=block;}

        inline constexpr Block GetBlock(std::size_t index)const{return blocks[index];}
        inline constexpr Block GetBlock(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const{return blocks[xIndex, yIndex, zIndex];}
        inline constexpr Block GetBlock(const Math::Vector3Int& index)const{return blocks[index.x, index.y, index.z];}

        inline constexpr bool HasBlock(std::size_t index)const{return !GetBlock(index).IsAir();}
        inline constexpr bool HasBlock(std::size_t xIndex, std::size_t yIndex, std::size_t zIndex)const{return !GetBlock(xIndex, yIndex, zIndex).IsAir();}
        inline constexpr bool HasBlock(const Math::Vector3Int& index)const{return !GetBlock(index).IsAir();}
    };


    class Chunk : public ChunkBase<32>
    {
    private:
        const Math::Vector3Int coord;
        Collections::Array3D<Block, 32> blocks;
        std::array<Chunk*, 6> neighbors;
        ChunkManager* manager;


    public:
        Chunk(ChunkManager& chunkManager, const Math::Vector3Int chunkCoord);
        Chunk(ChunkManager& chunkManager, int coordX, int coordY, int coordZ);
        Chunk(ChunkManager& chunkManager, const Math::Vector3Int chunkCoord, Chunk* neighborLeft, Chunk* neighborRight, Chunk* neighborFront, Chunk* neighborBack,
        Chunk* neighborTop, Chunk* neighborBottom);

    public: // Chunk Level Functions
        ChunkManager& GetManager();
        const ChunkManager& GetManager()const;

        bool HasAnyNeighbors()const;
        bool HasAllNeighbors()const;

        bool HasNeighbor(std::size_t index)const;
        bool HasNeighborLeft()const;
        bool HasNeighborRight()const;
        bool HasNeighborFront()const;
        bool HasNeighborBack()const;
        bool HasNeighborTop()const;
        bool HasNeighborBottom()const;

        bool HasNoNeighbor(std::size_t index)const;
        bool HasNoNeighborLeft()const;
        bool HasNoNeighborRight()const;
        bool HasNoNeighborFront()const;
        bool HasNoNeighborBack()const;
        bool HasNoNeighborTop()const;
        bool HasNoNeighborBottom()const;

        void SetNeighbors(Chunk& neighborLeft, Chunk& neighborRight, Chunk& neighborFront, Chunk& neighborBack, Chunk& neighborTop, Chunk& neighborBottom);
        void SetNeighbor(std::size_t index, Chunk& chunk);
        void SetNeighborLeft(Chunk& chunk);
        void SetNeighborRight(Chunk& chunk);
        void SetNeighborFront(Chunk& chunk);
        void SetNeighborBack(Chunk& chunk);
        void SetNeighborTop(Chunk& chunk);
        void SetNeighborBottom(Chunk& chunk);
        
        Chunk& GetNeighbor(std::size_t index);
        const Chunk& GetNeighbor(std::size_t index)const;
        Chunk& GetNeighborLeft();
        const Chunk& GetNeighborLeft()const;
        Chunk& GetNeighborRight();
        const Chunk& GetNeighborRight()const;
        Chunk& GetNeighborFront();
        const Chunk& GetNeighborFront()const;
        Chunk& GetNeighborBack();
        const Chunk& GetNeighborBack()const;
        Chunk& GetNeighborTop();
        const Chunk& GetNeighborTop()const;
        Chunk& GetNeighborBottom();
        const Chunk& GetNeighborBottom()const;

    public: // Block level functions
        bool BlockHasNeighborLeft(int x, int y, int z)const;
        bool BlockHasNeighborRight(int x, int y, int z)const;
        bool BlockHasNeighborFront(int x, int y, int z)const;
        bool BlockHasNeighborBack(int x, int y, int z)const;
        bool BlockHasNeighborTop(int x, int y, int z)const;
        bool BlockHasNeighborBottom(int x, int y, int z)const;








    };
}
