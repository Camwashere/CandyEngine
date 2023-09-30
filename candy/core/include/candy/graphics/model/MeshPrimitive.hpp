#pragma once
#include "MeshData.hpp"
namespace Candy::Graphics
{
  class MeshPrimitive
  {
  public:
    struct PlaneSettings
    {
      Color color=Color::white;
      size_t resolution=1;
      float width=1.0f;
      float height=1.0f;
    };
    struct CubeSettings
    {
      Color color=Color::white;
      size_t resolution=1;
      float width=1.0f;
      float height=1.0f;
      float depth=1.0f;
    };
    struct CylinderSettings
    {
      Color color=Color::white;
      size_t resolution=8;
      float topRadius=0.05f;
      float bottomRadius=0.05f;
      float height=1.0f;
    };
    
    struct ConeSettings
    {
      Color color=Color::white;
      size_t resolution=8;
      float radius=0.5f;
      float height=1.0f;
    };
    struct TorusSettings
    {
      Color color = Color::white;
      size_t tubeResolution = 8;
      size_t radialResolution = 8;
      float radius = 1.0f;
      float tubeRadius = 0.25f;
    };
  public:
    static MeshData<MeshVertex> GeneratePlane(const Color& color, size_t resolution=1, float width=1.0f, float height=1.0f);
    static MeshData<MeshVertex> GeneratePlane(const PlaneSettings& settings);
    
    
    static MeshData<MeshVertex> GenerateCube(const Color& color=Color::white, size_t resolution=1, float width=1.0f, float height=1.0f, float depth=1.0f);
    static MeshData<MeshVertex> GenerateCube(const CubeSettings& settings);
    
    static MeshData<MeshVertex> GenerateCylinder();
    static MeshData<MeshVertex> GenerateCylinder(const Color& color);
    static MeshData<MeshVertex> GenerateCylinder(const Color& color, size_t resolution, float radius=0.05f);
    static MeshData<MeshVertex> GenerateCylinder(const Color& color, size_t resolution, float topRadius, float bottomRadius, float height=1.0f);
    static MeshData<MeshVertex> GenerateCylinder(const CylinderSettings& settings);
    
    static MeshData<MeshVertex> GenerateCone(const Color& color);
    static MeshData<MeshVertex> GenerateCone(const ConeSettings& settings);
    
    static MeshData<MeshVertex> GenerateTorus(const Color& color);
    static MeshData<MeshVertex> GenerateTorus(const TorusSettings& settings);
    
    static const MeshData<MeshVertex> plane;
    static const MeshData<MeshVertex> cube;
    static const MeshData<MeshVertex> cylinder;
    static const MeshData<MeshVertex> cone;
    static const MeshData<MeshVertex> triangularPrism;
  };
}