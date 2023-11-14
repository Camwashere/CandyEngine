#pragma once
#include <cstdint>
namespace Candy
{
  enum class AssetType : uint32_t
  {
    Image=0,
    Texture,
    Font,
    Mesh,
    Shader,
    Animation,
    Model,
    Script,
    Scene,
    Unknown,
  };
}