#include <candy/graphics/model/ModelLoader.hpp>
#include <CandyPch.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace Candy::Graphics
{
  
  static Assimp::Importer importer;
  
  
  
  static MeshData ToMeshData(const aiMesh* mesh)
  {
    if (! mesh)
    {
      return {};
    }
    
    MeshData meshData{};
    
    // Load vertices
    for(unsigned int i = 0; i<mesh->mNumVertices; i++)
    {
      MeshVertex vertex{};
      
      aiVector3D pos = mesh->mVertices[i];
      vertex.position.Set(pos.x, pos.y, pos.z);
      
      if(mesh->HasNormals())
      {
        aiVector3D normal = mesh->mNormals[i];
        vertex.normal.Set(normal.x, normal.y, normal.z);
      }
      
      
      if(mesh->HasTextureCoords(0))
      {
        aiVector3D uv = mesh->mTextureCoords[0][i];
        vertex.uv.Set(uv.x, uv.y);
      }
      
      
      if(mesh->HasVertexColors(0))
      {
        aiColor4D color = mesh->mColors[0][i];
        vertex.color.Set(color.r, color.g, color.b, color.a);
      }
      meshData.vertices.push_back(vertex);
    }
    
    
    // Load indices
    for (uint32_t i=0; i<mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      for (uint32_t j=0; j<face.mNumIndices; j++)
      {
        uint32_t index = face.mIndices[j];
        meshData.indices.push_back(index);
      }
    }
    
    return meshData;
  }
  
  void ModelLoader::LoadModel(const std::filesystem::path& path)
  {
    unsigned int readFileFlags = aiProcess_CalcTangentSpace |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType;
    
    const aiScene* scene = importer.ReadFile(path.string(), readFileFlags);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      CANDY_CORE_ERROR("Assimp error: {0}", importer.GetErrorString());
      CANDY_CORE_ASSERT(false);
    }
    
    meshes.resize(scene->mNumMeshes);
    unsigned int maxMeshes = 10;
    
    // For each mesh
    for(unsigned int i = 0; i < maxMeshes; i++)
    {
      MeshData mesh = ToMeshData(scene->mMeshes[i]);
      if (mesh.IsValid())
      {
        meshes.push_back(mesh);
      }
      else
      {
        CANDY_CORE_ERROR("Invalid mesh in file from: {0}", path.string());
      }
    }
    
    for (uint32_t i=0; i<scene->mNumMaterials; i++)
    {
      aiMaterial* material = scene->mMaterials[i];
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
      {
        aiString path;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
        {
          std::string texturePath = path.C_Str();
          CANDY_CORE_INFO("Texture path: {0}", texturePath);
        }
      }
    }
  }

}