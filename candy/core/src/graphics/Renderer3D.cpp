#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
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
    static const uint32_t maxQuads = 20000;
    static const uint32_t maxVertices = maxQuads * 4;
    static const uint32_t maxIndices = maxQuads * 6;
    static const uint32_t maxObjects = 1000;
    
    Renderer3D::Stats stats;
    
    SharedPtr<Shader> gridShader;
    SharedPtr<Shader> meshShader;
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
    ShaderSettings gridSettings{};
    gridSettings.filepath = "assets/shaders/renderer3D/Grid.glsl";
    gridSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    gridSettings.depthTesting = true;
    gridSettings.alphaColorBlending = true;
    data.gridShader = Shader::Create(gridSettings);
  }
  void Renderer3D::InitMesh()
  {
    ShaderSettings meshSettings{};
    meshSettings.filepath = "assets/shaders/renderer3D/Mesh.glsl";
    meshSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    meshSettings.depthTesting = true;
    meshSettings.alphaColorBlending = true;
    data.meshShader = Shader::Create(meshSettings);
    
    data.meshVertexArray=VertexArray::Create();
    
    data.meshVertexBuffer=VertexBuffer::Create(data.meshShader->GetBufferLayout(), RenderData3D::maxVertices);
    data.meshIndexBuffer = IndexBuffer::Create(RenderData3D::maxIndices);
    
    data.meshVertexArray->AddVertexBuffer(data.meshVertexBuffer);
    data.meshVertexArray->SetIndexBuffer(data.meshIndexBuffer);
    
    data.meshVertexBufferBase = new MeshVertex[RenderData3D::maxVertices];
    data.meshIndexBufferBase = new uint32_t[RenderData3D::maxIndices];
  }
  void Renderer3D::InitSelection()
  {
    ShaderSettings selectionSettings{};
    selectionSettings.filepath = "assets/shaders/renderer3D/SelectionMesh.glsl";
    selectionSettings.renderPassIndex = Renderer::GetSelectionPassIndex();
    data.selectionShader = Shader::Create(selectionSettings);
  }
  
  void Renderer3D::InitMaterial()
  {
    data.whiteTexture = Texture::Create(TextureSpecification());
    uint32_t whiteTextureData = 0xffffffff;
    data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    
    data.textureSlots[0] = data.whiteTexture;
  }
  
  void Renderer3D::StartBatch()
  {
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
    Flush();
    StartBatch();
  }
  
  void Renderer3D::Flush()
  {
    if (data.meshIndexCount)
    {
      data.meshShader->Bind();
      
      uint32_t dataSize = (uint32_t)((uint8_t*)data.meshVertexBufferPtr - (uint8_t*)data.meshVertexBufferBase);
      data.meshVertexBuffer->SetData(data.meshVertexBufferBase, dataSize);
      data.meshIndexBuffer->SetData(data.meshIndexBufferBase, data.meshIndexCount);
      
      
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
        data.meshShader->PushInt("objectIndex", (int)data.objects[i].objectIndex);
        data.meshShader->PushInt("textureIndex", (int)data.objects[i].textureIndex);
        data.meshShader->PushFloat("tilingFactor", 1.0f);
        const auto& object = data.objects[i];
        RenderCommand::DrawIndexed(object.indexCount, 1, object.indexStart, object.vertexOffset, 0);
      }
      
    }
  }
  void Renderer3D::RenderGrid()
  {
    data.gridShader->Bind();
    data.gridShader->Commit();
    
    RenderCommand::DrawEmpty(6);
  }
  
  void Renderer3D::Init()
  {
    InitGrid();
    InitMesh();
    InitSelection();
    InitMaterial();
    ShaderLibrary::instance.Reload();
    
  }
  void Renderer3D::ResetStats()
  {
    data.stats.drawCalls=0;
    data.stats.objectCount=0;
    data.stats.vertexCount=0;
    data.stats.indexCount=0;
    data.stats.triangleCount=0;
  }
 
  
  void Renderer3D::BeginScene()
  {
    StartBatch();
    RenderGrid();
  }
 
  void Renderer3D::EndScene()
  {
    CANDY_CORE_ASSERT(data.transforms.size() == data.objects.size(), "Transforms and meshes are not the same size");
    Flush();
  }
  void Renderer3D::RenderSelectionBuffer()
  {
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
  void Renderer3D::SubmitMesh(uint32_t entity, const MeshData& mesh, const SharedPtr<Texture>& texture, const Math::Matrix4& transform)
  {
    if (mesh.IsValid())
    {
      if (data.meshIndexCount >= RenderData3D::maxIndices)
      {
        NextBatch();
      }
      
      ObjectData objectData{};
      objectData.objectIndex = data.objects.size();
      objectData.transformIndex = data.transforms.size();
      
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
      objectData.entityID = entity;
      objectData.indexStart = data.indexOffset;
      objectData.vertexOffset = data.vertexOffset;
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
      data.stats.vertexCount += mesh.vertices.size();
      data.stats.indexCount += mesh.indices.size();
      data.stats.triangleCount += mesh.indices.size() / 3;
      data.stats.drawCalls++;
    }
  }
  Renderer3D::Stats Renderer3D::GetStats()
  {
    return data.stats;
  }
}