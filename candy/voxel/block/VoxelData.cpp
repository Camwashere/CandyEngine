#include "VoxelData.hpp"

namespace Candy::Voxel{
        const Math::Vector3 VoxelData::voxelVerts[8] = {

                Math::Vector3(0, 0, 0), // 0
                Math::Vector3(1.0f, 0, 0), // 1
                Math::Vector3(1.0f, 1.0f, 0), // 2
                Math::Vector3(0, 1.0f, 0), // 3
                Math::Vector3(0, 0, 1.0f), // 4
                Math::Vector3(1.0f, 0, 1.0f), // 5
                Math::Vector3(1.0f, 1.0f, 1.0f), // 6
                Math::Vector3(0, 1.0f, 1.0f) // 7

        };
        const int VoxelData::voxelTris[6][4]= {

                // Back, Front, Top, Bottom, Left, Right

                // 0 1 2 2 1 3
                {0, 3, 1, 2}, // Back Face
                {5, 6, 4, 7}, // Front Face
                {3, 7, 2, 6}, // Top Face
                {1, 5, 0, 4}, // Bottom Face
                {4, 7, 0, 3}, // Left Face
                {1, 2, 5, 6} // Right Face

        };

        const Math::Vector3 VoxelData::voxelNormals[6]={
                Math::Vector3::back,
                Math::Vector3::forward,
                Math::Vector3::up,
                Math::Vector3::down,
                Math::Vector3::left,
                Math::Vector3::right
        };

        const Math::Vector2 VoxelData::voxelUvs[4]= {

                Math::Vector2 (0.0f, 0.0f),
                Math::Vector2 (0.0f, 1.0f),
                Math::Vector2 (1.0f, 0.0f),
                Math::Vector2 (1.0f, 1.0f)
        };
}