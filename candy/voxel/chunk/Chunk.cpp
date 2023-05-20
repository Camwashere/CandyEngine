#include "Chunk.hpp"
namespace Candy::Voxel {

        Chunk::Chunk(ChunkManager& chunkManager, const Math::Vector3Int chunkCoord) : ChunkBase<32>(chunkCoord), manager(&chunkManager) {

        }

        Chunk::Chunk(ChunkManager& chunkManager, int coordX, int coordY, int coordZ) : ChunkBase<32>(Math::Vector3Int(coordX, coordY, coordZ)), manager(&chunkManager)
        {

        }

        Chunk::Chunk(ChunkManager& chunkManager, const Math::Vector3Int chunkCoord,
                     Chunk* left, Chunk* right,
                     Chunk* front, Chunk* back,
                     Chunk* top, Chunk* bottom) : ChunkBase<32>(chunkCoord), manager(&chunkManager), neighbors({left, right, front, back, top, bottom}){
        }

        ChunkManager &Chunk::GetManager() {
            return *manager;
        }

        const ChunkManager &Chunk::GetManager() const {
            return *manager;
        }

        bool Chunk::HasAnyNeighbors() const {
            for (int i=0; i<neighbors.size(); i++)
            {
                if (HasNeighbor(i))
                {
                    return true;
                }
            }
            return false;
        }

        bool Chunk::HasAllNeighbors()const
        {
            for (int i=0; i<neighbors.size(); i++)
            {
                if (HasNoNeighbor(i))
                {
                    return false;
                }
            }
            return true;
        }

        bool Chunk::HasNeighbor(std::size_t index) const {
            return neighbors[index]!=nullptr;
        }

        bool Chunk::HasNeighborLeft() const {
            return neighbors[0]!=nullptr;
        }

        bool Chunk::HasNeighborRight() const {
            return neighbors[1]!=nullptr;
        }

        bool Chunk::HasNeighborFront() const {
            return neighbors[2]!=nullptr;
        }

        bool Chunk::HasNeighborBack() const {
            return neighbors[3]!=nullptr;
        }

        bool Chunk::HasNeighborTop() const {
            return neighbors[4]!=nullptr;
        }

        bool Chunk::HasNeighborBottom() const {
            return neighbors[5]!=nullptr;
        }

        bool Chunk::HasNoNeighbor(std::size_t index)const
        {
            return neighbors[index]==nullptr;
        }
        bool Chunk::HasNoNeighborLeft()const
        {
            return neighbors[0]==nullptr;
        }
        bool Chunk::HasNoNeighborRight()const
        {
            return neighbors[1]==nullptr;
        }
        bool Chunk::HasNoNeighborFront()const
        {
            return neighbors[2]==nullptr;
        }
        bool Chunk::HasNoNeighborBack()const
        {
            return neighbors[3]==nullptr;
        }
        bool Chunk::HasNoNeighborTop()const
        {
            return neighbors[4]==nullptr;
        }
        bool Chunk::HasNoNeighborBottom()const
        {
            return neighbors[5]==nullptr;
        }

        void Chunk::SetNeighbors(Chunk &neighborLeft, Chunk &neighborRight, Chunk &neighborFront, Chunk &neighborBack,
                                 Chunk &neighborTop, Chunk &neighborBottom) {
            neighbors[0] = &neighborLeft;
            neighbors[1] = &neighborRight;
            neighbors[2] = &neighborFront;
            neighbors[3] = &neighborBack;
            neighbors[4] = &neighborTop;
            neighbors[5] = &neighborBottom;
        }

        void Chunk::SetNeighbor(std::size_t index, Chunk &chunk) {
            neighbors[index] = &chunk;

        }

        void Chunk::SetNeighborLeft(Chunk &chunk) {
            neighbors[0] = &chunk;
        }

        void Chunk::SetNeighborRight(Chunk &chunk) {
            neighbors[1] = &chunk;
        }

        void Chunk::SetNeighborFront(Chunk &chunk) {
            neighbors[2] = &chunk;
        }

        void Chunk::SetNeighborBack(Chunk &chunk) {
            neighbors[3] = &chunk;
        }

        void Chunk::SetNeighborTop(Chunk &chunk) {
            neighbors[4] = &chunk;
        }

        void Chunk::SetNeighborBottom(Chunk &chunk) {
            neighbors[5] = &chunk;
        }

        Chunk &Chunk::GetNeighbor(std::size_t index) {
            return *neighbors[index];
        }

        const Chunk &Chunk::GetNeighbor(std::size_t index) const {
            return *neighbors[index];
        }

        Chunk &Chunk::GetNeighborLeft() {
            return *neighbors[0];
        }

        const Chunk &Chunk::GetNeighborLeft() const {
            return *neighbors[0];
        }

        Chunk &Chunk::GetNeighborRight() {
            return *neighbors[1];
        }

        const Chunk &Chunk::GetNeighborRight() const {
            return *neighbors[1];
        }

        Chunk &Chunk::GetNeighborFront() {
            return *neighbors[2];
        }

        const Chunk &Chunk::GetNeighborFront() const {
            return *neighbors[2];
        }

        Chunk &Chunk::GetNeighborBack() {
            return *neighbors[3];
        }

        const Chunk &Chunk::GetNeighborBack() const {
            return *neighbors[3];
        }

        Chunk &Chunk::GetNeighborTop() {
            return *neighbors[4];
        }

        const Chunk &Chunk::GetNeighborTop() const {
            return *neighbors[4];
        }

        Chunk &Chunk::GetNeighborBottom() {
            return *neighbors[5];
        }

        const Chunk &Chunk::GetNeighborBottom() const {
            return *neighbors[5];
        }

        bool Chunk::BlockHasNeighborLeft(int x, int y, int z) const {
            if (x==0)
            {
                return false;
            }
            return HasBlock(x-1, y, z);
        }

        bool Chunk::BlockHasNeighborRight(int x, int y, int z) const {
            if (x==Size()-1)
            {
                return false;
            }
            return HasBlock(x+1, y, z);
        }

        bool Chunk::BlockHasNeighborFront(int x, int y, int z) const {
            if (z==Size()-1)
            {
                return false;
            }
            return HasBlock(x, y, z+1);
        }

        bool Chunk::BlockHasNeighborBack(int x, int y, int z) const {
            if (z==0)
            {
                return false;
            }
            return HasBlock(x, y, z-1);
        }

        bool Chunk::BlockHasNeighborTop(int x, int y, int z) const {
            if (y == Size()-1)
            {
                return false;
            }
            return HasBlock(x, y+1, z);
        }

        bool Chunk::BlockHasNeighborBottom(int x, int y, int z) const {
            if (y==0)
            {
                return false;
            }
            return HasBlock(x, y-1, z);
        }

}