#include <candy/graphics/model/MeshData.hpp>
#include <CandyPch.hpp>
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
  
  
  MeshVertexColored::MeshVertexColored() : position(Vector3::zero), color(Color::white)
  {
  
  }
  MeshVertexColored::MeshVertexColored(const MeshVertexColored& other) : position(other.position), color(other.color)
  {
  
  }
  MeshVertexColored::MeshVertexColored(const Math::Vector3& positionValue, const Color& colorValue) : position(positionValue), color(colorValue)
  {
  
  }
  
  MeshVertexColored& MeshVertexColored::operator=(const MeshVertexColored& other)
  {
    position = other.position;
    color = other.color;
    return *this;
    
  }
  bool MeshVertexColored::operator==(const MeshVertexColored& other)const
  {
    return position == other.position && color == other.color;
  }
  bool MeshVertexColored::operator!=(const MeshVertexColored& other)const
  {
    return !(*this == other);
  }
  
  std::string MeshVertexColored::ToString()const
  {
    std::string str = "Position: " + position.ToString() + ", " + "Color: " + color.ToString();
    return str;
  }
  
  MeshVertex::MeshVertex() : position(Vector3::zero), color(Color::white), normal(Vector3::up), uv(Vector2::zero)
  {
  
  }
  
  MeshVertex::MeshVertex(const MeshVertex& other) : position(other.position), color(other.color), normal(other.normal), uv(other.uv)
  {
  
  }
  MeshVertex::MeshVertex(const Math::Vector3& positionValue, const Color& colorValue, const Math::Vector3& normalValue, const Math::Vector2& uvValue) : position(positionValue), color(colorValue), normal(normalValue), uv(uvValue)
  {
  
  }
  
  MeshVertex& MeshVertex::operator=(const MeshVertex& other)
  {
    position = other.position;
    color = other.color;
    normal = other.normal;
    uv = other.uv;
    return *this;
  }
  bool MeshVertex::operator==(const MeshVertex& other)const
  {
    return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
  }
  bool MeshVertex::operator!=(const MeshVertex& other)const
  {
    return !(*this == other);
  }
  
  std::string MeshVertex::ToString()const
  {
    
    std::string str = "Position: " + position.ToString() + ", " + "Color: " + color.ToString() + ", " + "Normal: " + normal.ToString() + ", " + "UV: " + uv.ToString();
    return str;
    
  }
  
  /*MeshData::MeshData() : vertices{}, indices{}
  {
  
  }
  MeshData::MeshData(const MeshData& other) : vertices(other.vertices), indices(other.indices)
  {
  
  }
  MeshData::MeshData(const std::vector<MeshVertex>& verticesValue, const std::vector<uint32_t>& indicesValue) : vertices(verticesValue), indices(indicesValue)
  {
  
  }
  
  MeshData& MeshData::operator=(const MeshData& other)
  {
    CANDY_PROFILE_FUNCTION();
    vertices.resize(other.vertices.size());
    indices.resize(other.indices.size());
    for (int i=0; i<other.vertices.size(); i++)
    {
      vertices[i] = other.vertices[i];
    }
    for (int i=0; i<other.indices.size(); i++)
    {
      indices[i] = other.indices[i];
    }
    return *this;
  }
  bool MeshData::operator==(const MeshData& other)const
  {
    CANDY_PROFILE_FUNCTION();
    if(vertices.size() != other.vertices.size() || indices.size() != other.indices.size())
    {
      return false;
    }
    for (int i=0; i<vertices.size(); i++)
    {
      if(vertices[i] != other.vertices[i])
      {
        CANDY_CORE_ERROR("Vert not equal: {0} != {1}", vertices[i].ToString(), other.vertices[i].ToString());
        return false;
      }
    }
    for (int i=0; i<indices.size(); i++)
    {
      if(indices[i] != other.indices[i])
      {
        CANDY_CORE_ERROR("Index not equal: {0} != {1}", indices[i], other.indices[i]);
        return false;
      }
    }
    return true;
  }
  bool MeshData::operator!=(const MeshData& other)const
  {
    CANDY_PROFILE_FUNCTION();
    return !(*this == other);
  }
  static MeshData CreatePlaneMeshData()
  {
    MeshData mesh{};
    mesh.vertices.resize(4);
    
    mesh.indices = { 0, 2, 1, 0, 3, 2};
    
    for (int i=0; i<4; i++)
    {
      MeshVertex vertex{};
      vertex.position = planeVerts[i];
      vertex.uv = planeUVs[i];
      vertex.normal = Vector3::up;
      vertex.color = Color::white;
      mesh.vertices[i] = vertex;
    }
    
    return mesh;
  }
  static MeshData CreateCubeMeshData()
  {
    unsigned int vertexIndex=0;
    MeshData mesh{};
    
    for (int p=0; p<6; p++)
    {
      std::array<MeshVertex, 4> verts{};
      
      for (int i=0; i<4; i++)
      {
        verts[i].position = voxelVerts [voxelTris [p][i]];
        verts[i].normal = voxelNormals[p];
        verts[i].uv = voxelUvs[i];
        verts[i].color = Color::white;
        mesh.vertices.push_back(verts[i]);
      }
      
      
      
      mesh.indices.push_back(vertexIndex);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 3);
      vertexIndex += 4;
      
      
      
    }
    
    
    return mesh;
  }
  static MeshData CreateTriangularPrismMeshData()
  {
    MeshData mesh{};
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
  
  const MeshData MeshData::plane(CreatePlaneMeshData());
  const MeshData MeshData::cube(CreateCubeMeshData());
  const MeshData MeshData::triangularPrism(CreateTriangularPrismMeshData());
  
  bool MeshData::IsValid()const
  {
    CANDY_PROFILE_FUNCTION();
    if(indices.size() % 3 != 0)
    {
      return false;
    }
    
    return !(vertices.empty() || indices.empty());
    
  }
  bool MeshData::Empty()const
  {
    return vertices.empty() && indices.empty();
  }
  size_t MeshData::VertexCount()const
  {
    return vertices.size();
  }
  size_t MeshData::IndexCount()const
  {
    return indices.size();
  }
  
  std::string MeshData::ToString()const
  {
    CANDY_PROFILE_FUNCTION();
    std::string str;
    for (int i=0; i<vertices.size(); i++)
    {
      str += vertices[i].ToString() + "\n";
    }
    
    return str;
    
  }*/
  
  static MeshData<MeshVertex> CreatePlaneMeshData()
  {
    MeshData<MeshVertex> mesh{};
    mesh.vertices.resize(4);
    
    mesh.indices = { 0, 2, 1, 0, 3, 2};
    
    for (int i=0; i<4; i++)
    {
      MeshVertex vertex{};
      vertex.position = planeVerts[i];
      vertex.uv = planeUVs[i];
      vertex.normal = Vector3::up;
      vertex.color = Color::white;
      mesh.vertices[i] = vertex;
    }
    
    return mesh;
  }
  static MeshData<MeshVertex> CreateCubeMeshData()
  {
    unsigned int vertexIndex=0;
    MeshData<MeshVertex> mesh{};
    
    for (int p=0; p<6; p++)
    {
      std::array<MeshVertex, 4> verts{};
      
      for (int i=0; i<4; i++)
      {
        verts[i].position = voxelVerts [voxelTris [p][i]];
        verts[i].normal = voxelNormals[p];
        verts[i].uv = voxelUvs[i];
        verts[i].color = Color::white;
        mesh.vertices.push_back(verts[i]);
      }
      
      
      
      mesh.indices.push_back(vertexIndex);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 2);
      mesh.indices.push_back(vertexIndex + 1);
      mesh.indices.push_back(vertexIndex + 3);
      vertexIndex += 4;
      
      
      
    }
    
    
    return mesh;
  }
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
        float x = (float)j * stepX - halfSizeX;
        float z = (float)i * stepZ - halfSizeZ;
        
        //Adjust orientation
        Math::Vector3 pos(x, 0, z);
        
        meshData.vertices.emplace_back(pos, settings.color, Vector3::zero, Vector2::zero);
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
      
      // Two vertices at each point along the circle to form the cylinder, but shifted by -halfHeight
      bottomIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(bottomX, -halfHeight, bottomZ), settings.color, Vector3::zero, Vector2::zero);
      
      topIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(topX, halfHeight, topZ), settings.color, Vector3::zero, Vector2::zero);
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
    meshData.vertices.emplace_back(Vector3(0, -halfHeight, 0), settings.color, Vector3::zero, Vector2::zero);
    
    uint32_t topCenterIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, halfHeight, 0), settings.color, Vector3::zero, Vector2::zero);
    
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
    
    // Generate the cone
    for (size_t i = 0; i <= settings.resolution; i++)
    {
      // Angle along the circle
      float theta = (float)i / (float)settings.resolution * 2.0f * Math::PI;
      
      // X and Z coordinates of the point on the circle for the bottom
      float bottomX = settings.radius * Cos(theta);
      float bottomZ = settings.radius * Sin(theta);
      
      // Bottom vertices of the cone
      bottomIndices.push_back(meshData.vertices.size());
      meshData.vertices.emplace_back(Vector3(bottomX, -halfHeight, bottomZ), settings.color, Vector3::zero, Vector2::zero);
    }
    
    // Single top vertex of the cone
    uint32_t topIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, halfHeight, 0), settings.color, Vector3::zero, Vector2::zero);
    
    // Generate the indices for the cone sides
    for (unsigned int i = 0; i < settings.resolution; i++)
    {
      meshData.indices.push_back(bottomIndices[i]);
      meshData.indices.push_back(topIndex);
      meshData.indices.push_back(bottomIndices[(i+1)%settings.resolution]);
    }
    
    // Center vertex for the bottom
    uint32_t bottomCenterIndex = meshData.vertices.size();
    meshData.vertices.emplace_back(Vector3(0, -halfHeight, 0), settings.color, Vector3::zero, Vector2::zero);
    
    // Generate the indices for the bottom face
    for (int i = 0; i < settings.resolution; i++)
    {
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
        
        float tubeX = settings.tubeRadius * Cos(tubeAngle);       // tube X coordinate
        float tubeY = settings.tubeRadius * Sin(tubeAngle);       // tube Y coordinate
        
        float centerX = (settings.radius + tubeX) * Cos(radialAngle); // final X coordinate
        float centerY = (settings.radius + tubeX) * Sin(radialAngle); // final Y coordinate
        
        meshData.vertices.emplace_back(Vector3(centerX, centerY, tubeY), settings.color, Vector3::zero, Vector2::zero);
        
        // Compute indices
        size_t curIndex = i * settings.tubeResolution + j;
        size_t nextIndex = i * settings.tubeResolution + ((j + 1) % settings.tubeResolution);
        size_t nextRadialIndex = ((i + 1) % settings.radialResolution) * settings.tubeResolution + j;
        size_t nextRadialNextIndex = ((i + 1) % settings.radialResolution) * settings.tubeResolution + ((j + 1) % settings.tubeResolution);
        
        // Two triangles to form a surface
        meshData.indices.push_back(curIndex);
        meshData.indices.push_back(nextIndex);
        meshData.indices.push_back(nextRadialNextIndex);
        
        meshData.indices.push_back(curIndex);
        meshData.indices.push_back(nextRadialNextIndex);
        meshData.indices.push_back(nextRadialIndex);
      }
    }
    
    return meshData;
  }
  
  const MeshData<MeshVertex> MeshPrimitive::plane(CreatePlaneMeshData());
  const MeshData<MeshVertex> MeshPrimitive::cube(CreateCubeMeshData());
  const MeshData<MeshVertex> MeshPrimitive::cylinder(GenerateCylinder(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::cone(GenerateCone(Color::white));
  const MeshData<MeshVertex> MeshPrimitive::triangularPrism(CreateTriangularPrismMeshData());
  
}