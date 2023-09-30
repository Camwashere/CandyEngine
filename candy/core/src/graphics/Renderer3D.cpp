#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/texture/Texture.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  
  struct ObjectData
  {
    uint32_t transformIndex;
    uint32_t textureIndex;
    uint32_t objectIndex;
    uint32_t entityID;
    uint32_t indexStart;
    int32_t vertexOffset;
    uint32_t indexCount;
    
  };
  struct RenderData3D
  {
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    static const uint32_t maxTriangles = 100'000;
    static const uint32_t maxVertices = maxTriangles * 3;
    static const uint32_t maxIndices = maxTriangles * 3;
    static const uint32_t maxObjects = 1000;
    
    Renderer3D::Stats stats;
    
    SharedPtr<Shader> gridShader;
    SharedPtr<Shader> meshShader;
    SharedPtr<Shader> gizmoShader;
    uint32_t meshShaderObjectIndexID=0;
    uint32_t meshShaderTextureIndexID=0;
    uint32_t meshShaderTilingFactorID=0;
   
    SharedPtr<Shader> selectionShader;
    uint32_t meshIndexCount = 0;
    uint32_t vertexOffset = 0;
    uint32_t indexOffset = 0;
    MeshVertex* meshVertexBufferBase = nullptr;
    MeshVertex* meshVertexBufferPtr = nullptr;
    uint32_t* meshIndexBufferBase = nullptr;
    uint32_t* meshIndexBufferPtr = nullptr;
    
    SharedPtr<VertexArray> meshVertexArray;
    SharedPtr<VertexBuffer> meshVertexBuffer;
    SharedPtr<IndexBuffer> meshIndexBuffer;
    
    
    
    SharedPtr<Texture> whiteTexture;
    std::array<SharedPtr<Texture>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture, 1 = statue texture
    
    std::vector<ObjectData> objects;
    std::vector<Matrix4> transforms;
    
  };
  
  static RenderData3D data;
  
  
  void Renderer3D::InitGrid()
  {
    CANDY_PROFILE_FUNCTION();
    ShaderSettings gridSettings{};
    gridSettings.configs.push_back(PipelineConfigSettings{RenderMode::Shaded});
    gridSettings.filepath = "assets/shaders/renderer3D/Grid.glsl";
    gridSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    gridSettings.depthTesting = true;
    gridSettings.alphaColorBlending = true;
    
    data.gridShader = Shader::Create(gridSettings);
  }
  void Renderer3D::InitMesh()
  {
    CANDY_PROFILE_FUNCTION();
    ShaderSettings meshSettings{};
    meshSettings.filepath = "assets/shaders/renderer3D/Mesh.glsl";
    meshSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    meshSettings.depthTesting = true;
    meshSettings.alphaColorBlending = true;
    meshSettings.configs.push_back(PipelineConfigSettings{RenderMode::Shaded});
    meshSettings.configs.push_back(PipelineConfigSettings{RenderMode::Wireframe});
    
    data.meshShader = Shader::Create(meshSettings);
    
    data.meshVertexArray=VertexArray::Create();
    
    data.meshVertexBuffer=VertexBuffer::Create(data.meshShader->GetBufferLayout(), RenderData3D::maxVertices);
    data.meshIndexBuffer = IndexBuffer::Create(RenderData3D::maxIndices);
    
    data.meshVertexArray->AddVertexBuffer(data.meshVertexBuffer);
    data.meshVertexArray->SetIndexBuffer(data.meshIndexBuffer);
    
    data.meshVertexBufferBase = new MeshVertex[RenderData3D::maxVertices];
    data.meshIndexBufferBase = new uint32_t[RenderData3D::maxIndices];
    
    data.meshShaderObjectIndexID = data.meshShader->GetPushID("objectIndex");
    data.meshShaderTextureIndexID = data.meshShader->GetPushID("textureIndex");
    data.meshShaderTilingFactorID = data.meshShader->GetPushID("tilingFactor");
  }
  
  
  void Renderer3D::InitSelection()
  {
    CANDY_PROFILE_FUNCTION();
    ShaderSettings selectionSettings{};
    selectionSettings.configs.push_back(PipelineConfigSettings{RenderMode::Shaded});
    selectionSettings.filepath = "assets/shaders/renderer3D/SelectionMesh.glsl";
    selectionSettings.renderPassIndex = Renderer::GetSelectionPassIndex();
    data.selectionShader = Shader::Create(selectionSettings);
  }
  
  void Renderer3D::InitMaterial()
  {
    CANDY_PROFILE_FUNCTION();
    
    data.whiteTexture = Texture::White();
    
    data.textureSlots[0] = data.whiteTexture;
  }
  
  void Renderer3D::StartBatch()
  {
    CANDY_PROFILE_FUNCTION();
    data.objects.clear();
    data.transforms.clear();
    
    data.meshIndexCount = 0;
    data.meshVertexBufferPtr = data.meshVertexBufferBase;
    data.meshIndexBufferPtr = data.meshIndexBufferBase;
    
    
    ResetStats();
    data.vertexOffset=0;
    data.indexOffset=0;
    data.textureSlotIndex = 1;
    
  }
  void Renderer3D::NextBatch()
  {
    CANDY_PROFILE_FUNCTION();
    Flush();
    StartBatch();
  }
  void Renderer3D::FlushVertexData()
  {
    if (skipFlush)
    {
      skipFlush=false;
      return;
    }
    uint32_t dataSize = (uint32_t)((uint8_t*)data.meshVertexBufferPtr - (uint8_t*)data.meshVertexBufferBase);
    data.meshVertexBuffer->SetData(data.meshVertexBufferBase, dataSize);
    data.meshIndexBuffer->SetData(data.meshIndexBufferBase, data.meshIndexCount);
    
  }
  void Renderer3D::Flush()
  {
    CANDY_PROFILE_FUNCTION();
    if (data.meshIndexCount)
    {
      data.meshShader->Bind();
      
      
      FlushVertexData();
      
      
      
      data.meshShader->Bind();
      
      Renderer::GetCurrentFrame().storageBuffer->SetData(data.transforms.data(), sizeof(Matrix4) * data.transforms.size());
      
      DescriptorBuilder builder = DescriptorBuilder::Begin();
      VkDescriptorBufferInfo objectInfo;
      objectInfo.buffer = *Renderer::GetCurrentFrame().storageBuffer;
      objectInfo.offset=0;
      objectInfo.range=sizeof(Matrix4) * data.transforms.size();
      builder.AddBufferWrite(0, &objectInfo, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);
      builder.Write(Renderer::GetCurrentFrame().ObjectDescriptor());
      
      // Bind textures
      std::vector<VkDescriptorImageInfo> imageInfos{};
      for (uint32_t i=0; i<data.textureSlotIndex; i++)
      {
        CANDY_CORE_ASSERT(data.textureSlots[i] != nullptr);
        
        VkDescriptorImageInfo imageInfo = data.textureSlots[i]->GetDescriptorImageInfo();
        imageInfos.push_back(imageInfo);
      }
      for (uint32_t i=data.textureSlotIndex; i<RenderData3D::maxTextureSlots; i++)
      {
        VkDescriptorImageInfo imageInfo = data.whiteTexture->GetDescriptorImageInfo();
        imageInfos.push_back(imageInfo);
      }
      DescriptorBuilder textureBuilder = DescriptorBuilder::Begin();
      textureBuilder.AddImageArrayWrite(0, imageInfos, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MATERIAL_SET);
      textureBuilder.Write();
      
      
      data.meshShader->Commit();
      data.meshVertexArray->Bind();
      for (int i=0; i<data.objects.size(); i++)
      {
        
        data.meshShader->PushInt(data.meshShaderObjectIndexID, (int)data.objects[i].objectIndex);
        data.meshShader->PushInt(data.meshShaderTextureIndexID, (int)data.objects[i].textureIndex);
        data.meshShader->PushFloat(data.meshShaderTilingFactorID, 1.0f);
        const auto& object = data.objects[i];
        RenderCommand::DrawIndexed(object.indexCount, 1, object.indexStart, object.vertexOffset, 0);
      }
      
    }
    
  }
  void Renderer3D::RenderGrid()
  {
    CANDY_PROFILE_FUNCTION();
    data.gridShader->Bind();
    data.gridShader->Commit();
    
    RenderCommand::DrawEmpty(6);
  }
  
  void Renderer3D::Init()
  {
    CANDY_PROFILE_FUNCTION();
    InitGrid();
    InitMesh();
    InitSelection();
    InitMaterial();
    ShaderLibrary::Reload();
    
  }
  void Renderer3D::ResetStats()
  {
    CANDY_PROFILE_FUNCTION();
    data.stats.drawCalls=0;
    data.stats.objectCount=0;
    data.stats.vertexCount=0;
    data.stats.indexCount=0;
    data.stats.triangleCount=0;
  }
 
  
  void Renderer3D::BeginScene()
  {
    CANDY_PROFILE_FUNCTION();
    StartBatch();
    RenderGrid();
  }
 
  void Renderer3D::EndScene()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(data.transforms.size() == data.objects.size(), "Transforms and meshes are not the same size");
    Flush();
  }
  void Renderer3D::RenderSelectionBuffer()
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(data.transforms.size() == data.objects.size(), "Transforms and meshes are not the same size");
    Renderer::BeginSelectionPass();
    data.selectionShader->Bind();
    
    data.selectionShader->Commit();
    data.selectionShader->PushInt("entityID", -1);
    data.meshVertexArray->Bind();
    for (int i=0; i<data.objects.size(); i++)
    {
      const auto& object = data.objects[i];
      data.selectionShader->PushInt("objectIndex", i);
      data.selectionShader->PushInt("entityID", static_cast<int>(object.entityID));
      RenderCommand::DrawIndexed(object.indexCount, 1, object.indexStart, object.vertexOffset, 0);
    }
  }
  void Renderer3D::SubmitMesh(uint32_t entity, const MeshData<MeshVertex>& mesh, const SharedPtr<Texture>& texture, const Math::Matrix4& transform)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(mesh.IsValid(), "Error, invalid mesh");
    CANDY_CORE_ASSERT(mesh.IndexCount() < RenderData3D::maxIndices, "Error, mesh has too many indices");
    CANDY_CORE_ASSERT(mesh.VertexCount() < RenderData3D::maxVertices, "Error, mesh has too many vertices");
    if (data.meshIndexCount >= RenderData3D::maxIndices)
    {
      NextBatch();
    }
    
    
    ObjectData objectData{};
    objectData.objectIndex = data.objects.size();
    objectData.transformIndex = data.transforms.size();
    
    if (texture)
    {
      bool found = false;
      
      for (int i=0; i<data.textureSlotIndex; i++)
      {
        if (*data.textureSlots[i] == *texture)
        {
          found = true;
          objectData.textureIndex = i;
          break;
        }
      }
      if (! found)
      {
        CANDY_CORE_ASSERT(data.textureSlotIndex < data.maxTextureSlots, "Texture slots are full");
        data.textureSlots[data.textureSlotIndex] = texture;
        objectData.textureIndex = data.textureSlotIndex;
        data.textureSlotIndex++;
      }
    }
    else
    {
      objectData.textureIndex = 0;
    }
    
    
    
    objectData.entityID = entity;
    objectData.indexStart = data.indexOffset;
    objectData.vertexOffset = (int32_t)data.vertexOffset;
    objectData.indexCount = mesh.IndexCount();
    
    data.objects.push_back(objectData);
    data.transforms.push_back(transform);
    
    for (size_t i = 0; i < mesh.VertexCount(); i++)
    {
      *data.meshVertexBufferPtr = mesh.vertices[i];
      data.meshVertexBufferPtr++;
      
    }
    
    for (uint32_t i : mesh.indices)
    {
      *data.meshIndexBufferPtr = i;
      data.meshIndexBufferPtr++;
    }
    data.meshIndexCount += mesh.IndexCount();
    data.vertexOffset += mesh.VertexCount();
    data.indexOffset += mesh.IndexCount();
    
    data.stats.objectCount++;
    data.stats.vertexCount += mesh.VertexCount();
    data.stats.indexCount += mesh.IndexCount();
    data.stats.triangleCount += mesh.IndexCount() / 3;
    data.stats.drawCalls++;
  }
  
  void Renderer3D::SubmitMesh(uint32_t entity, uint32_t meshIndexCount, uint32_t meshVertexCount, const SharedPtr<Texture>& texture, const Math::Matrix4& transform)
  {
    CANDY_PROFILE_FUNCTION();
    CANDY_CORE_ASSERT(meshIndexCount < RenderData3D::maxIndices, "Error, mesh has too many indices");
    CANDY_CORE_ASSERT(meshVertexCount < RenderData3D::maxVertices, "Error, mesh has too many vertices");
    if (data.meshIndexCount >= RenderData3D::maxIndices)
    {
      NextBatch();
    }
    
    
    ObjectData objectData{};
    objectData.objectIndex = data.objects.size();
    objectData.transformIndex = data.transforms.size();
    
    if (texture)
    {
      bool found = false;
      
      for (int i=0; i<data.textureSlotIndex; i++)
      {
        if (*data.textureSlots[i] == *texture)
        {
          found = true;
          objectData.textureIndex = i;
          break;
        }
      }
      if (! found)
      {
        CANDY_CORE_ASSERT(data.textureSlotIndex < data.maxTextureSlots, "Texture slots are full");
        data.textureSlots[data.textureSlotIndex] = texture;
        objectData.textureIndex = data.textureSlotIndex;
        data.textureSlotIndex++;
      }
    }
    else
    {
      objectData.textureIndex = 0;
    }
    
    
    
    objectData.entityID = entity;
    objectData.indexStart = data.indexOffset;
    objectData.vertexOffset = (int32_t)data.vertexOffset;
    objectData.indexCount = meshIndexCount;
    data.objects.push_back(objectData);
    data.transforms.push_back(transform);
    
    
    data.meshIndexCount += meshIndexCount;
    data.vertexOffset += meshVertexCount;
    data.indexOffset += meshIndexCount;
    
    data.stats.objectCount++;
    data.stats.vertexCount += meshVertexCount;
    data.stats.indexCount += meshIndexCount;
    data.stats.triangleCount += meshIndexCount / 3;
    data.stats.drawCalls++;
  }
  Renderer3D::Stats Renderer3D::GetStats()
  {
    return data.stats;
  }
}