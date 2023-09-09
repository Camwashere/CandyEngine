#include <candy/graphics/Renderer3D.hpp>
#include <candy/graphics/RenderCommand.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/shader/ShaderLibrary.hpp>
namespace Candy::Graphics
{
  using namespace Math;
  Renderer3DStats Renderer3D::stats{};
  Renderer3D* Renderer3D::instance = nullptr;
  
  
  struct RenderData3D
  {
    static const uint32_t maxTextureSlots = 32; // TODO: RenderCaps
    
    SharedPtr<Texture> whiteTexture;
    std::array<SharedPtr<Texture>, maxTextureSlots> textureSlots;
    uint32_t textureSlotIndex = 1; // 0 = white texture, 1 = statue texture
    
  };
  
  static RenderData3D data;
  
  void Renderer3D::Initialize()
  {
    ShaderSettings gridSettings{};
    gridSettings.filepath = "assets/shaders/renderer3D/Grid.glsl";
    gridSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    gridSettings.depthTesting = true;
    gridSettings.alphaColorBlending = true;
    gridShader = Shader::Create(gridSettings);
    
    ShaderSettings shaderSettings{};
    shaderSettings.filepath = "assets/shaders/renderer3D/Mesh.glsl";
    shaderSettings.renderPassIndex = Renderer::GetViewportPassIndex();
    shaderSettings.depthTesting = true;
    shaderSettings.alphaColorBlending = true;
    meshShader = Shader::Create(shaderSettings);
    
    ShaderSettings selectionSettings{};
    selectionSettings.filepath = "assets/shaders/renderer3D/SelectionMesh.glsl";
    selectionSettings.renderPassIndex = Renderer::GetSelectionPassIndex();
    selectionShader = Shader::Create(selectionSettings);
    
    
    data.whiteTexture = Texture::Create(TextureSpecification());
    uint32_t whiteTextureData = 0xffffffff;
    data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    
    data.textureSlots[0] = data.whiteTexture;
    //data.textureSlots[1] = texture;
    data.textureSlotIndex = 2;
    
  }
  
  void Renderer3D::RenderGrid()
  {
    instance->gridShader->Bind();
    
    instance->gridShader->Commit();
    
    RenderCommand::DrawEmpty(6);
  }
  
  void Renderer3D::Init()
  {
    instance=new Renderer3D();
    instance->Initialize();
    ShaderLibrary::instance.Reload();
  }
  void Renderer3D::ResetStats()
  {
    stats.drawCalls=0;
    stats.objects=0;
    stats.vertices=0;
    stats.indices=0;
    stats.triangles=0;
  }
  BufferLayout Renderer3D::GetBufferLayout()
  {
    return instance->meshShader->GetBufferLayout();
  }
  
  void Renderer3D::BeginScene()
  {
    instance->transforms.clear();
    instance->meshes.clear();
    instance->entities.clear();
    instance->textureIndices.clear();
    data.textureSlotIndex = 1;
    ResetStats();
    RenderGrid();
  }
 
  void Renderer3D::EndScene()
  {
    CANDY_CORE_ASSERT(instance->transforms.size() == instance->meshes.size(), "Transforms and meshes are not the same size");
    instance->meshShader->Bind();
    
    Renderer::GetCurrentFrame().storageBuffer->SetData(instance->transforms.data(), sizeof(Matrix4) * instance->transforms.size());
    
    DescriptorBuilder builder = DescriptorBuilder::Begin();
    VkDescriptorBufferInfo objectInfo;
    objectInfo.buffer = *Renderer::GetCurrentFrame().storageBuffer;
    objectInfo.offset=0;
    objectInfo.range=sizeof(Matrix4) * instance->transforms.size();
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
    
    
    instance->meshShader->Commit();
    
    for (int i=0; i<instance->meshes.size(); i++)
    {
      instance->meshes[i].vertexArray->Bind();
      instance->meshShader->PushInt("objectIndex", i);
      instance->meshShader->PushInt("textureIndex", (int)instance->textureIndices[i]);
      RenderCommand::DrawIndexed(instance->meshes[i].vertexArray);
    }
  }
  void Renderer3D::RenderSelectionBuffer()
  {
    CANDY_CORE_ASSERT(instance->transforms.size() == instance->meshes.size(), "Transforms and meshes are not the same size");
    Renderer::BeginSelectionPass();
    instance->selectionShader->Bind();
    
    
    instance->selectionShader->Commit();
    instance->selectionShader->PushInt("entityID", -1);
    for (int i=0; i<instance->meshes.size(); i++)
    {
      instance->meshes[i].vertexArray->Bind();
      instance->selectionShader->PushInt("objectIndex", i);
      instance->selectionShader->PushInt("entityID", static_cast<int>(instance->entities[i]));
      RenderCommand::DrawIndexed(instance->meshes[i].vertexArray);
    }
   
  }
  void Renderer3D::SubmitMesh(uint32_t entity, const Mesh& mesh, const SharedPtr<Texture>& texture, const Math::Matrix4& transform)
  {
    if (mesh.IsValid())
    {
      stats.objects++;
      stats.vertices += mesh.vertexArray->GetVertexCount();
      stats.indices += mesh.vertexArray->GetIndexCount();
      stats.drawCalls++;
      stats.triangles += mesh.vertexArray->GetIndexCount() / 3;
      instance->meshes.push_back(mesh);
      instance->transforms.push_back(transform);
      bool found = false;
      for (int i=0; i<data.textureSlotIndex; i++)
      {
        if (*data.textureSlots[i] == *texture)
        {
          found = true;
          instance->textureIndices.push_back(i);
          break;
        }
      }
      if (! found)
      {
        CANDY_CORE_ASSERT(data.textureSlotIndex < data.maxTextureSlots, "Texture slots are full");
        data.textureSlots[data.textureSlotIndex] = texture;
        instance->textureIndices.push_back(data.textureSlotIndex);
        data.textureSlotIndex++;
      }
      instance->entities.push_back(entity);
    }
  }
  Renderer3DStats Renderer3D::GetStats()
  {
    return stats;
  }
}