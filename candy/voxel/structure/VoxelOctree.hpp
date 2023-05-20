#pragma once
#include "../chunk/ChunkAll.hpp"
namespace Candy::Voxel {

    constexpr const uint MAX_VOXEL_OCTREE_DEPTH=16;

    class VoxelOctreeNode;

    class VoxelOctree
    {
    private:
        VoxelOctreeNode* root;

    public:
        inline constexpr uint GetMaxDepth()const{return MAX_VOXEL_OCTREE_DEPTH;}
    };


    class VoxelOctreeNode
    {
    private:
        VoxelOctreeNode* parent;
        std::array<VoxelOctreeNode*, 8> children;
        const Math::Vector3 position;
        const float size;
        const uint depth;

    public:
        VoxelOctreeNode(float nodeSize);
        VoxelOctreeNode(VoxelOctreeNode* parentNode, const Math::Vector3& nodePosition, float nodeSize, uint nodeDepth);
        ~VoxelOctreeNode();

    public:
        bool Subdivide();
        VoxelOctreeNode& GetChild(uint index);
        std::array<VoxelOctreeNode*, 8>& GetChildren();

    public:
        Math::Vector3 GetMaxCorner()const;

    public:
        inline const Math::Vector3& GetPosition()const{return position;}
        inline uint GetSize()const{return size;}
        inline uint GetDepth()const{return depth;}
        inline bool HasChildren()const{return children[0]!=nullptr;}
        inline bool IsRoot()const{return parent==nullptr;}
        inline bool IsChild()const{return parent!=nullptr;}
        inline bool IsBottom()const{return depth==GetMaxDepth();}
        inline VoxelOctreeNode& GetParent(){return *parent;}
        inline constexpr uint GetMaxDepth()const{return MAX_VOXEL_OCTREE_DEPTH;}
    };
}
