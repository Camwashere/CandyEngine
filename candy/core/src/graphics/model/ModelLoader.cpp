#include <candy/graphics/model/ModelLoader.hpp>
#include <CandyPch.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <candy/ecs/Entity.hpp>
#include <candy/ecs/BaseComponents.hpp>
namespace Candy::Graphics
{
  using namespace ECS;
  using namespace Math;
  
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
  
  static Matrix4 ToMatrix4(const aiMatrix4x4& aiMatrix)
  {
    Matrix4 result;
    result.GetColumn(0) = Vector4(aiMatrix.a1, aiMatrix.b1, aiMatrix.c1, aiMatrix.d1);
    result.GetColumn(1) = Vector4(aiMatrix.a2, aiMatrix.b2, aiMatrix.c2, aiMatrix.d2);
    result.GetColumn(2) = Vector4(aiMatrix.a3, aiMatrix.b3, aiMatrix.c3, aiMatrix.d3);
    result.GetColumn(3) = Vector4(aiMatrix.a4, aiMatrix.b4, aiMatrix.c4, aiMatrix.d4);
    return result;
  }
  
  static void ProcessNode(aiNode* node, const aiScene* aiScene, Entity parent, SharedPtr<Scene> scene, SharedPtr<Texture> texture)
  {
    // For each mesh
    uint32_t maxMeshes = node->mNumMeshes;
   
    
    Matrix4 localTransform = ToMatrix4(node->mTransformation);
    
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    if (! Matrix4::DecomposeTransform(localTransform, position, rotation, scale))
    {
      CANDY_CORE_ASSERT(false, "Failed to decompose transform!");
      
    }
    
    Entity groupEntity = scene->CreateEntity(node->mName.C_Str());
    groupEntity.GetTransform().SetLocal(position, rotation, scale);
    if (parent)
    {
      groupEntity.SetParent(parent);
    }
    for(unsigned int i = 0; i < maxMeshes; i++)
    {
      
      MeshData mesh = ToMeshData(aiScene->mMeshes[node->mMeshes[i]]);
      
      
      if (mesh.IsValid())
      {
        Entity entity = scene->CreateEntity(aiScene->mMeshes[node->mMeshes[i]]->mName.C_Str());
        
        //entity.GetTransform().SetLocal(position, rotation, scale);
        entity.AddComponent<MeshFilterComponent>(mesh);
        entity.AddComponent<MeshRendererComponent>(texture);
        if (groupEntity)
        {
          entity.SetParent(groupEntity);
        }
        
        
        
      }
      else
      {
        CANDY_CORE_ASSERT(false, "Mesh not valid! Failed to load model!");
      }
      
    }
    
    if (node->mNumChildren > 0)
    {
      for (uint32_t i=0; i<node->mNumChildren; i++)
      {
        ProcessNode(node->mChildren[i], aiScene, groupEntity, scene, texture);
      }
    }
    
    
    
  }
  
  void ModelLoader::LoadModel(const std::filesystem::path& path)
  {
    unsigned int readFileFlags = aiProcess_CalcTangentSpace |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType;
    
    const aiScene* aiScene = importer.ReadFile(path.string(), readFileFlags);
    
    if(!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
      CANDY_CORE_ERROR("Assimp error: {0}", importer.GetErrorString());
      CANDY_CORE_ASSERT(false);
    }
    
    aiNode* rootNode = aiScene->mRootNode;
    
    SharedPtr<Texture> texture = Texture::Create("assets/models/backpack/1001_albedo.jpg");
    
    
    ProcessNode(rootNode, aiScene, Entity{}, scene, texture);
    
    
    
    
   
    
    /*for (uint32_t i=0; i<scene->mNumMaterials; i++)
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
    }*/
  }

}