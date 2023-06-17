cmake_minimum_required(VERSION 3.25)
project(CandyMath)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE_MATH_FILES general/MathOps.hpp linalg/LinalgForwardDef.hpp linalg/vector/base/VectorBase.hpp
        linalg/vector/base/VectorExpression.hpp linalg/vector/Vector2.hpp linalg/vector/Vector2.cpp
        linalg/vector/VectorAll.hpp linalg/LinalgAll.hpp linalg/vector/Vector3.hpp linalg/vector/Vector4.hpp linalg/vector/Vector3.cpp
        linalg/vector/Vector4.cpp linalg/vector/Vector2Int.hpp linalg/vector/Vector3Int.hpp linalg/vector/Vector2Int.cpp linalg/vector/Vector3Int.cpp
        linalg/quaternion/Quaternion.hpp linalg/quaternion/Quaternion.cpp linalg/matrix/Matrix4.hpp linalg/matrix/Matrix4.cpp general/Random.hpp general/Random.cpp
        general/Range.hpp general/Limit.hpp linalg/matrix/base/Matrix.hpp linalg/matrix/MatrixAll.hpp general/MathGeneralAll.hpp direction/Direction2.hpp direction/Direction2.cpp direction/Direction3.hpp
        direction/Direction3.cpp geometry/2d/Rectangle.hpp geometry/2d/Rectangle.cpp geometry/GeometryAll.hpp)



add_library(${PROJECT_NAME} ${SOURCE_MATH_FILES} CandyMath.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC CandyBase)
target_include_directories(${PROJECT_NAME} PUBLIC ../base)



