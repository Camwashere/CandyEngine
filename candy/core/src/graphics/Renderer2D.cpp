#include <candy/graphics/Renderer2D.hpp>
#include <candy/math/Vector.hpp>
#include <candy/math/Matrix.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  struct QuadVertex
  {
    Vector3 position;
    Vector4 color;
    Vector2 uv;
    float textureIndex;
    float tilingFactor;
  };
}