#include <candy/graphics/model/MeshPrimitive.hpp>

namespace Candy::Graphics
{
  using namespace Math;
  
  static const Vector3 planeVerts[4] = {
  Vector3(-0.5f, 0.0f, -0.5f), // 0
  Vector3(0.5f, 0.0f, -0.5f), // 1
  Vector3(0.5f, 0.0f, 0.5f), // 2
  Vector3(-0.5f, 0.0f, 0.5f) // 3
  };
  
  static const Vector2 planeUVs[4] = {
  Vector2(0.0f, 0.0f),
  Vector2(1.0f, 0.0f),
  Vector2(1.0f, 1.0f),
  Vector2(0.0f, 1.0f)
  };
  
  
  
  static const Vector3 voxelVerts[8] = {
  Vector3(-0.5f, -0.5f, -0.5f), // 0
  Vector3(0.5f, -0.5f, -0.5f), // 1
  Vector3(0.5f, 0.5f, -0.5f), // 2
  Vector3(-0.5f, 0.5f, -0.5f), // 3
  Vector3(-0.5f, -0.5f, 0.5f), // 4
  Vector3(0.5f, -0.5f, 0.5f), // 5
  Vector3(0.5f, 0.5f, 0.5f), // 6
  Vector3(-0.5f, 0.5f, 0.5f) // 7
  
  };
  static const unsigned int voxelTris[6][4]= {
  
  // Back, Front, Top, Bottom, Left, Right
  
  // 0 1 2 2 1 3
  {0, 3, 1, 2}, // Back Face
  {5, 6, 4, 7}, // Front Face
  {3, 7, 2, 6}, // Top Face
  {1, 5, 0, 4}, // Bottom Face
  {4, 7, 0, 3}, // Left Face
  {1, 2, 5, 6} // Right Face
  
  };
  
  static const Vector3 voxelNormals[6]={
  Vector3(0, 0, -1),
  Vector3(0, 0, 1),
  Vector3(0, 1, 0),
  Vector3(0, -1, 0),
  Vector3(-1, 0, 0),
  Vector3(1, 0, 0)
  };
  
  static const Vector2 voxelUvs[4]= {
  
  Vector2 (0.0f, 1.0f),
  Vector2 (0.0f, 0.0f),
  Vector2 (1.0f, 1.0f),
  Vector2 (1.0f, 0.0f)
  };
  
  static const std::vector<Vector3> triangularPrismVertices = {
  // Bottom face
  { -0.5f, -0.5f,  -0.5f },
  {  0.5f, -0.5f,  -0.5f },
  {  0.0f, -0.5f,   0.5f },
  // Top face
  { -0.5f, 0.5f,  -0.5f },
  {  0.5f, 0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  // Side face 1
  { -0.5f, -0.5f,  -0.5f },
  {  0.5f, -0.5f,  -0.5f },
  { -0.5f, 0.5f,  -0.5f },
  {  0.5f, 0.5f,  -0.5f },
  // Side face 2
  {  0.5f, -0.5f,  -0.5f },
  {  0.0f, -0.5f,   0.5f },
  {  0.5f, 0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  // Side face 3
  {  0.0f, -0.5f,   0.5f },
  { -0.5f, -0.5f,  -0.5f },
  {  0.0f, 0.5f,   0.5f },
  { -0.5f, 0.5f,  -0.5f }
  };
  static const std::vector<uint32_t> triangularPrismIndices = {
  0, 1, 2,  // Bottom face
  5, 4, 3,  // Top face
  6, 8, 7,  7, 8, 9,  // Side face 1
  10, 12, 11, 11, 12, 13,  // Side face 2
  14, 16, 15, 15, 16, 17   // Side face 3
  };
  static const std::vector<Vector3> triangularPrismNormals = {
  // Bottom face
  { 0.0f, -1.0f, 0.0f },
  { 0.0f, -1.0f, 0.0f },
  { 0.0f, -1.0f, 0.0f },
  // Top face
  { 0.0f, 1.0f, 0.0f },
  { 0.0f, 1.0f, 0.0f },
  { 0.0f, 1.0f, 0.0f },
  // Side face 1
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  { 0.0f, 0.0f, -1.0f },
  // Side face 2
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  { 1.0f, 0.0f, 0.0f },
  // Side face 3
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  { -1.0f, 0.0f, 0.0f },
  };
  
  static const std::vector<Vector2> triangularPrismUvs = {
  // Bottom face
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.5f, 0.0f },
  // Top face
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.5f, 0.0f },
  // Side face 1
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f },
  // Side face 2
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f },
  // Side face 3
  { 0.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 1.0f, 0.0f }
  };
  
  
  
  static MeshData<MeshVertex> CreateTriangularPrismMeshData()
  {
    MeshData<MeshVertex> mesh{};
    for (int i=0; i<triangularPrismVertices.size(); i++)
    {
      MeshVertex vertex{};
      vertex.position = triangularPrismVertices[i];
      vertex.color = Color::white;
      vertex.normal = triangularPrismNormals[i];
      vertex.uv = triangularPrismUvs[i];
      mesh.vertices.push_back(vertex);
    }
    
    mesh.indices = triangularPrismIndices;
    return mesh;
  }
  MeshData<MeshVertex> MeshPrimitive::GeneratePlane(const Color& color, size_t resolution, float width, float height)
  {
    return GeneratePlane({color, resolution, width, height});
  }
  
  MeshData<MeshVertex> MeshPrimitive::GeneratePlane(const PlaneSettings& settings)
  {
    MeshData<MeshVertex> meshData{};
    
    const float sizeX = settings.width;
    const float sizeZ = settings.height;
    const float stepX = sizeX / (float)settings.resolution;
    const float stepZ = sizeZ / (float)settings.resolution;
    const float halfSizeX = sizeX * 0.5f;
    const float halfSizeZ = sizeZ * 0.5f;
    
    for (size_t i = 0; i <= settings.resolution; ++i)
    {
      for (size_t j = 0; j <= settings.resolution; ++j)
      {
        float x = static_cast<float>(j) * stepX - halfSizeX;
        float z = static_cast<float>(i) * stepZ - halfSizeZ;
        
        // UV coordinates
        float u = static_cast<float>(j) / static_cast<float>(settings.resolution);
        float v = static_cast<float>(i) / static_cast<float>(settings.resolution);
        
        // Adjust orientation
        Math::Vector3 pos(x, 0, z);
        
        meshData.vertices.emplace_back(pos, settings.color, Vector3::up, Vector2(u, v));
      }
    }
    
    for (size_t i = 0; i < settings.resolution; ++i)
    {
      for (size_t j = 0; j < settings.resolution; ++j)
      {
        unsigned int topLeft = i * (settings.resolution + 1) + j;
        unsigned int topRight = topLeft + 1;
        unsigned int bottomLeft = (i + 1) * (settings.resolution + 1) + j;
        unsigned int bottomRight = bottomLeft + 1;
        
        // Triangle 1
        meshData.indices.push_back(topLeft);
        meshData.indices.push_back(bottomLeft);
        meshData.indices.push_back(topRight);
        
        // Triangle 2
        meshData.indices.push_back(topRight);
        meshData.indices.push_back(bottomLeft);
        meshData.indices.push_back(bottomRight);
      }
    }
    
    return meshData;
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCube(const Color& color, size_t resolution, float width, float height, float depth)
  {
    return GenerateCube({color, resolution, width, height, depth});
  }
  
  MeshData<MeshVertex> MeshPrimitive::GenerateCube(const CubeSettings& settings)
  {
    MeshData<MeshVertex> meshData;
    uint32_t vertexIndex=0;
    float widthOffset = settings.width/2.0f;
    float heightOffset = settings.height/2.0f;
    float depthOffset = settings.depth/2.0f;
    float delta = 1.0f / (float)settings.resolution;
    
    for (int p=0; p<6; p++)
    {
      for (int i=0; i<4; i++)
      {
        MeshVertex vertex{};
        vertex.position = voxelVerts [voxelTris [p][i]];
        
        
        vertex.position.x *= widthOffset;
        vertex.position.y *= heightOffset;
        vertex.position.z *= depthOffset;
        vertex.normal = voxelNormals[p];
        vertex.uv = voxelUvs[i];
        vertex.color = settings.color;
        meshData.vertices.push_back(vertex);
      }
      
      
      
      meshData.indices.push_back(vertexIndex);
      meshData.indices.push_back(vertexIndex + 1);
      meshData.indices.push_back(vertexIndex + 2);
      meshData.indices.push_back(vertexIndex + 2);
      meshData.indices.push_back(vertexIndex + 1);
      meshData.indices.push_back(vertexIndex + 3);
      vertexIndex += 4;
     
    }
    return meshData;
  }
  
  MeshData<MeshVertex> MeshPrimitive::GenerateCylinder()
  {
    return GenerateCylinder(CylinderSettings{});
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCylinder(const Color& color)
  {
    CylinderSettings settings{};
    settings.color = color;
    return GenerateCylinder(settings);
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCylinder(const Color& color, size_t resolution, float radius)
  {
    CylinderSettings settings{};
    settings.color = color;
    settings.resolution = resolution;
    settings.topRadius = radius;
    settings.bottomRadius = radius;
    return GenerateCylinder(settings);
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCylinder(const Color& color, size_t resolution, float topRadius, float bottomRadius, float height)
  {
    return GenerateCylinder({color, resolution, topRadius, bottomRadius, height});
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCylinder(const CylinderSettings& settings)
  {
    MeshData<MeshVertex> meshData{};
    std::vector<uint32_t> bottomIndices, topIndices;
    
    float halfHeight = settings.height / 2.0f;
    
    // Generate the cylinder
    for (size_t i = 0; i <= settings.resolution; i++)
    {
      // Angle along the circle
      float theta = (float)i / (float)settings.resolution * 2.0f * Math::PI;
      
      // X and Z coordinates of the point on the circle for both the top and the bottom
      float topX = settings.topRadius * Cos(theta);
      float topZ = settings.topRadius * Sin(theta);
      
      float bottomX = settings.bottomRadius * Cos(theta);
      float bottomZ = settings.bottomRadius * Sin(theta);
      
      // UV coordinates
      float u = static_cast<float>(i) / static_cast<float>(settings.resolution);
      
      //Normal
      Vector3 bottomNormal = Vector3(bottomX, 0.0f, bottomZ).Normalized();
      Vector3 topNormal = Vector3(topX, 0.0f, topZ).Normalized();
      
      // Two vertices at each point along the circle to form the cylinder, but shifted by -halfHeight
      bottomIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(bottomX, -halfHeight, bottomZ), settings.color, bottomNormal, Vector2(u, 1.0f));
      
      topIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(topX, halfHeight, topZ), settings.color, topNormal, Vector2(u, 0.0f));
    }
    
    // Generate the indices for the cylinder sides
    for (unsigned int i = 0; i < settings.resolution; i++)
    {
      meshData.indices.push_back(bottomIndices[i]);
      meshData.indices.push_back(topIndices[i]);
      meshData.indices.push_back(topIndices[i+1]);
      
      meshData.indices.push_back(topIndices[i+1]);
      meshData.indices.push_back(bottomIndices[i+1]);
      meshData.indices.push_back(bottomIndices[i]);
    }
    
    // Center vertices for the top and bottom, also shifted by -halfHeight
    uint32_t bottomCenterIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, -halfHeight, 0), settings.color, Vector3::down, Vector2(0.5f, 0.5f));
    
    uint32_t topCenterIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, halfHeight, 0), settings.color, Vector3::up, Vector2(0.5f, 0.5f));
    
    // Create n-gon faces for the top and bottom
    for(int i = 0; i < settings.resolution; i++) {
      // bottom
      meshData.indices.push_back(bottomCenterIndex);
      meshData.indices.push_back(bottomIndices[i]);
      meshData.indices.push_back(bottomIndices[i + 1]);
      
      // top
      meshData.indices.push_back(topCenterIndex);
      meshData.indices.push_back(topIndices[i+1]);
      meshData.indices.push_back(topIndices[i]);
    }
    
    return meshData;
  }
  
  MeshData<MeshVertex> MeshPrimitive::GenerateCone(const Color& color)
  {
    ConeSettings settings{};
    settings.color = color;
    return GenerateCone(settings);
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateCone(const ConeSettings& settings)
  {
    MeshData<MeshVertex> meshData{};
    std::vector<uint32_t> bottomIndices;
    
    float halfHeight = settings.height / 2.0f;
    float slope = Sqrt(settings.height * settings.height + settings.radius * settings.radius);
    
    // Generate the cone
    for (size_t i = 0; i <= settings.resolution; i++)
    {
      // Angle along the circle
      float theta = (float)i / (float)settings.resolution * 2.0f * Math::PI;
      
      // X and Z coordinates of the point on the circle for the bottom
      float bottomX = settings.radius * Cos(theta);
      float bottomZ = settings.radius * Sin(theta);
      
      //Normal
      Vector3 normal = Vector3(bottomX, settings.height * settings.radius/slope, bottomZ).Normalized();
      
      // UV coordinates
      float u = (float)i / float(settings.resolution);
      
      // Bottom vertices of the cone
      bottomIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(bottomX, -halfHeight, bottomZ), settings.color, normal, Vector2(u, 1.0f));
    }
    
    // Single top vertex of the cone
    uint32_t topIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, halfHeight, 0), settings.color, Vector3::up, Vector2(0.5f, 0.5f));
    
    // Generate the indices for the cone sides
    for (unsigned int i = 0; i < settings.resolution; i++)
    {
      // Swap indices order for correct winding
      meshData.indices.push_back(topIndex);
      meshData.indices.push_back(bottomIndices[(i+1)%settings.resolution]);
      meshData.indices.push_back(bottomIndices[i]);
    }
    
    // Center vertex for the bottom
    uint32_t bottomCenterIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, -halfHeight, 0), settings.color, Vector3::down, Vector2(0.5f, 0.5f));
    
    // Generate the indices for the bottom face
    for (int i = 0; i < settings.resolution; i++)
    {
      // Swap indices order for correct winding
      meshData.indices.push_back(bottomCenterIndex);
      meshData.indices.push_back(bottomIndices[i]);
      meshData.indices.push_back(bottomIndices[(i+1)%settings.resolution]);
    }
    
    return meshData;
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateTorus(const Color& color)
  {
    TorusSettings settings{};
    settings.color = color;
    return GenerateTorus(settings);
  }
  MeshData<MeshVertex> MeshPrimitive::GenerateTorus(const TorusSettings& settings)
  {
    MeshData<MeshVertex> meshData{};
    
    for (size_t i = 0; i < settings.radialResolution; i++)
    {
      for (size_t j = 0; j < settings.tubeResolution; j++)
      {
        // Compute angles for radial and tube circles
        float radialAngle = (float)i / (float)settings.radialResolution * 2.0f * Math::PI;
        float tubeAngle = (float)j / (float)settings.tubeResolution * 2.0f * Math::PI;
        
        // Compute coordinates on the tube circle
        float tubeX = settings.tubeRadius * Cos(tubeAngle);       // tube X coordinate
        float tubeY = settings.tubeRadius * Sin(tubeAngle);       // tube Y coordinate
        
        // Compute final position of the vertex
        float centerX = (settings.radius + tubeX) * Cos(radialAngle); // final X coordinate
        float centerY = (settings.radius + tubeX) * Sin(radialAngle); // final Y coordinate
        
        // Compute the normal by subtracting the tube center position from the vertex position,
        // then normalize the result.
        Vector3 tubeCenter((settings.radius + tubeX), 0, 0);
        Vector3 normal = Vector3(centerX, centerY, tubeY) - tubeCenter;
        normal.Normalize();
        
        // UV coordinates
        float u = (float)i / (float)settings.radialResolution;
        float v = (float)j / (float)settings.tubeResolution;
        
        
        meshData.vertices.emplace_back(Vector3(centerX, centerY, tubeY), settings.color, normal, Vector2(u, v));
        
        // Compute indices
        size_t curIndex = i * settings.tubeResolution + j;
        size_t nextIndex = i * settings.tubeResolution + ((j + 1) % settings.tubeResolution);
        size_t nextRadialIndex = ((i + 1) % settings.radialResolution) * settings.tubeResolution + j;
        size_t nextRadialNextIndex = ((i + 1) % settings.radialResolution) * settings.tubeResolution + ((j + 1) % settings.tubeResolution);
        
        // Two triangles to form a surface
        meshData.indices.push_back(curIndex);
        meshData.indices.push_back(nextRadialNextIndex);
        meshData.indices.push_back(nextIndex);
        
        meshData.indices.push_back(curIndex);
        meshData.indices.push_back(nextRadialIndex);
        meshData.indices.push_back(nextRadialNextIndex);
      }
    }
    
    return meshData;
  }
  
  const MeshData<MeshVertex> MeshPrimitive::plane(GeneratePlane(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::cube(GenerateCube(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::cylinder(GenerateCylinder(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::cone(GenerateCone(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::triangularPrism(CreateTriangularPrismMeshData());
}