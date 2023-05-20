#include "VoxelOctree.hpp"

namespace Candy{
    using namespace Math;
    namespace Voxel{
        VoxelOctreeNode::VoxelOctreeNode(float nodeSize) : parent(nullptr),  size(nodeSize), depth(0)
        {

        }
        VoxelOctreeNode::VoxelOctreeNode(VoxelOctreeNode* parentNode, const Vector3& nodePosition, float nodeSize, uint nodeDepth) : parent(parentNode), position(nodePosition), size(nodeSize), depth(nodeDepth)
        {

        }
        VoxelOctreeNode::~VoxelOctreeNode()
        {
            for (int i=0; i<children.size(); i++)
            {
                delete children[i];
            }
            delete parent;
        }

        Math::Vector3 VoxelOctreeNode::GetMaxCorner()const
        {
            return {position.x+size, position.y+size, position.z+size};
        }

        bool VoxelOctreeNode::Subdivide()
        {
            if (depth==GetMaxDepth() || HasChildren())
            {
                return false;
            }

            uint childDepth = depth+1;
            float childSize = size/2.0f;

            children[0] = new VoxelOctreeNode(this, position, childSize, childDepth);
            children[1] = new VoxelOctreeNode(this, Vector3(position.x+childSize, position.y, position.z), childSize, childDepth);
            children[2] = new VoxelOctreeNode(this, Vector3(position.x, position.y+childSize, position.z), childSize, childDepth);
            children[3] = new VoxelOctreeNode(this, Vector3(position.x, position.y, position.z+childSize), childSize, childDepth);

            children[4] = new VoxelOctreeNode(this, Vector3(position.x+childSize, position.y+childSize, position.z), childSize, childDepth);
            children[5] = new VoxelOctreeNode(this, Vector3(position.x+childSize, position.y, position.z+childSize), childSize, childDepth);
            children[6] = new VoxelOctreeNode(this, Vector3(position.x, position.y+childSize, position.z+childSize), childSize, childDepth);
            children[7] = new VoxelOctreeNode(this, Vector3(position.x+childSize, position.y+childSize, position.z+childSize), childSize, childDepth);
            return true;
        }

        VoxelOctreeNode& VoxelOctreeNode::GetChild(uint index)
        {
            return *children[index];
        }
        std::array<VoxelOctreeNode*, 8>& VoxelOctreeNode::GetChildren()
        {
            return children;
        }
}}