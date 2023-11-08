#include <candy/graphics/model/ModelLoader.hpp>
#include <CandyPch.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <candy/ecs/Entity.hpp>
#include <candy/ecs/BaseComponents.hpp>
#include <candy/project/ProjectManager.hpp>
namespace Candy::Graphics
{
  using namespace ECS;
  using namespace Math;
  
  
  
  ModelLoader::ModelLoader(const SharedPtr<ECS::Scene>& sceneValue) : scene(sceneValue)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(scene);
    importer = new Assimp::Importer();
  }
  
  ModelLoader::~ModelLoader()
  {
    CANDY_PROFILE_FUNCTION();
    delete importer;
  }
  
  static MeshData<Graphics::MeshVertex> ToMeshData(const aiMesh* mesh)
  {
    CANDY_PROFILE_FUNCTION();
    if (! mesh)
    {
      return {};
    }
    
    MeshData<Graphics::MeshVertex> meshData{};
    
    
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
    CANDY_PROFILE_FUNCTION();
    Matrix4 result;
    result.GetColumn(0) = Vector4(aiMatrix.a1, aiMatrix.b1, aiMatrix.c1, aiMatrix.d1);
    result.GetColumn(1) = Vector4(aiMatrix.a2, aiMatrix.b2, aiMatrix.c2, aiMatrix.d2);
    result.GetColumn(2) = Vector4(aiMatrix.a3, aiMatrix.b3, aiMatrix.c3, aiMatrix.d3);
    result.GetColumn(3) = Vector4(aiMatrix.a4, aiMatrix.b4, aiMatrix.c4, aiMatrix.d4);
    return result;
  }
  
  void ModelLoader::ProcessNode(aiNode* node, const aiScene* aiScene, const Entity& parent, const SharedPtr<Texture>& texture)
  {
    CANDY_PROFILE_FUNCTION();
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
        ProcessNode(node->mChildren[i], aiScene, groupEntity, texture);
      }
    }
    
    
    
  }
 /* static void LoadMaterialTextures(aiTextureType type, aiMaterial* material)
  {
    for (uint32_t i=0; i<material->GetTextureCount(type); i++)
    {
      
      aiString path;
      material->GetTexture(type, i, &path);
      
      std::string texturePath = path.C_Str();
      
    }
  }*/
  void ModelLoader::LoadModel(const std::filesystem::path& path)
  {
    CANDY_PROFILE_FUNCTION();
    unsigned int readFileFlags = aiProcess_Triangulate | aiProcess_FlipUVs;
    
    const aiScene* aiScene = importer->ReadFile(path.string(), readFileFlags);
    
    if(!aiScene || aiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
      CANDY_CORE_ERROR("Assimp error: {0}", importer->GetErrorString());
      CANDY_CORE_ASSERT(false);
    }
    
    aiNode* rootNode = aiScene->mRootNode;
    
    CANDY_CORE_INFO("Children: {0}, Meshes: {1}", rootNode->mNumChildren, aiScene->mNumMeshes);
    
    SharedPtr<Texture> texture = Texture::Create(ProjectManager::GetAssetsDirectory() / "models" / "backpack" / "1001_albedo.jpg");
    
    CANDY_CORE_INFO("Material count: {}", aiScene->mNumMaterials);
    
    
    
    
    ProcessNode(rootNode, aiScene, Entity{}, texture);
    
    
  }

}