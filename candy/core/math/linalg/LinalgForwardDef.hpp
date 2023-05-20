#pragma once
#include <cstddef>
#include <string>
#include <ostream>
#include "vector/base/VectorBase.hpp"

namespace Candy::Math
{
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Vector2Int;
    struct Vector3Int;
    struct Quaternion;
    struct Matrix4;
    template<typename T, std::size_t ROW_SIZE, std::size_t COLUMN_SIZE, std::size_t MAX_SIZE>
    struct Matrix;
    
}