#pragma once
#include <Candy/Math.hpp>
namespace Candy::Voxel {
    struct VoxelData
    {
        static const Math::Vector3 voxelVerts[8];
        static const int voxelTris[6][4];
        static const Math::Vector3 voxelNormals[6];
        static const Math::Vector2 voxelUvs[4];

        // REORDER NUMBERS
        static constexpr const int LeftFace=4;
        static constexpr const int RightFace=5;

        static constexpr const int BackFace=0;
        static constexpr const int FrontFace=1;
        static constexpr const int TopFace=2;
        static constexpr const int BottomFace=3;


    };
}

