#include "ExampleLayer.hpp"
#include "imgui.h"
#include "imgui_internal.h"
using namespace Candy;
using namespace Graphics;
using namespace Math;
using namespace std;

ExampleLayer::ExampleLayer()
        : Layer("ExampleLayer"), camera(), chunkRenderer(), editor("Dockspace")
{
    /*CreateShaderResources();
    
    Mesh chunkMesh = chunkRenderer.ToMesh();
    Mesh lightMesh = Mesh::CreateCubeMesh();
    InitializePrimaryShader(chunkMesh);
    InitializeLightingShader(lightMesh);
    editor.SetRightPane("Right");
    
    //RenderCommand::SetRenderingMode(Candy::Graphics::RenderingMode::WIREFRAME);
    editor.GetRightPane().AddWidget(new UI::Button("Wireframe", Vector2(0, 0), Vector2(50, 50), Color::blue, Color::green, Color::red));
    editor.GetRightPane().AddWidget(new UI::DragVector3("Light position", &light.position));
    editor.GetRightPane().AddWidget(new UI::ColorPicker("Light Color", &light.color));
    editor.GetRightPane().AddWidget(new UI::DragFloat("Light Ambient", &light.ambientStrength, 0.01f, 0.0f, 1.0f));
    editor.GetRightPane().AddSpacer();
    editor.GetRightPane().AddWidget(new UI::DragFloat("Metallic", &material.metallic, 0.01f, 0.0f, 1.0f));
    editor.GetRightPane().AddWidget(new UI::DragFloat("Specular", &material.specular, 0.01f, 0.0f, Math::MAX_FLOAT));
    editor.GetRightPane().AddWidget(new UI::DragFloat("Roughness", &material.roughness, 0.1f, 0.0f, Math::MAX_FLOAT));*/
    
}
void ExampleLayer::CreateShaderResources()
{
    vertexArray = VertexArray::Create();
    shader = Shader::Create("Bitch", "../sandbox/resources/shaders/vertexShader.glsl", "../sandbox/resources/shaders/fragShader.glsl");
    lightShader = Shader::Create("BItch1", "../sandbox/resources/shaders/lightVertexShader.glsl", "../sandbox/resources/shaders/lightFragShader.glsl");
    lightVertexArray = VertexArray::Create();
    texture1 = Texture::Create("../sandbox/resources/images/wall.jpg");
    texture2 = Texture::Create("../sandbox/resources/images/awesomeface.png");
}

void ExampleLayer::InitializeLightingShader(const Candy::Graphics::Mesh& mesh)
{
    /*SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(mesh.GetArray(), mesh.GetArraySize());
    BufferLayout layout = {
            {Graphics::ShaderDataType::Float3, "aPos"},
            {Graphics::ShaderDataType::Float3, "aNormal"},
            {Graphics::ShaderDataType::Float2, "aTexCoord"},
    };
    vertexBuffer->SetLayout(layout);
    lightVertexArray->AddVertexBuffer(vertexBuffer);
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(mesh.GetTriangleArray(), mesh.triangles.size());
    lightVertexArray->SetIndexBuffer(indexBuffer);
    lightVertexArray->Bind();
    
    lightShader->Bind();
    lightShader->SetVector3("lightColor", light.color);
    
    light.position.Set(1.2f, 1.0f, 2.0f);
    Matrix4 projection = Matrix4::Perspective(ToRadians(camera.zoom), Application::AspectRatio(), 0.1f, 100.f);
    lightShader->SetMatrix4("projection", projection);
    lightShader->SetMatrix4("view", camera.GetViewMatrix());*/
    
    
}

void ExampleLayer::InitializePrimaryShader(const Mesh& mesh)
{
    
    /*SharedPtr<VertexBuffer> vertexBuffer = VertexBuffer::Create(mesh.GetArray(), mesh.GetArraySize());
    BufferLayout layout = {
            {Graphics::ShaderDataType::Float3, "aPos"},
            {Graphics::ShaderDataType::Float3, "aNormal"},
            {Graphics::ShaderDataType::Float2, "aTexCoord"},
    };
    vertexBuffer->SetLayout(layout);
    vertexArray->AddVertexBuffer(vertexBuffer);
    SharedPtr<IndexBuffer> indexBuffer = IndexBuffer::Create(mesh.GetTriangleArray(), mesh.triangles.size());
    vertexArray->SetIndexBuffer(indexBuffer);
    vertexArray->Bind();
    
    shader->Bind();
    shader->SetInt("texture1", 0);
    shader->SetInt("texture2", 1);
    shader->SetLight("light", light);
    shader->SetMaterial("material", material);
    shader->SetVector3("viewPos", camera.position);
    
    
    Matrix4 projection = Matrix4::Perspective(ToRadians(camera.zoom), Application::AspectRatio(), 0.1f, 100.f);
    shader->SetMatrix4("projection", projection);
    shader->SetMatrix4("view", camera.GetViewMatrix());*/
}





void ExampleLayer::OnAttach()
{

}
void ExampleLayer::OnDetach()
{

}

void ExampleLayer::OnUpdate()
{
    /*camera.OnUpdate();
    RenderCommand::SetClearColor(Color(0.1f, 0.1f, 0.1f));
    RenderCommand::Clear();
    Renderer::BeginScene(camera);
    texture1->Bind();
    texture2->Bind(1);
    
    shader->Bind();
    shader->SetLight("light", light);
    shader->SetVector3("viewPos", camera.position);
    shader->SetMaterial("material", material);
    
    lightShader->Bind();
    lightShader->SetVector3("lightColor", light.color);
    
    Matrix4 transform = Matrix4::Scaled(Vector3(1.0f, 1.0f, 1.0f));
    
    Renderer::Submit(shader, vertexArray, transform);
    Matrix4 lightTransform = Matrix4::Translation(light.position);
    lightTransform = Matrix4::Scaled(lightTransform, Vector3(0.2f));
    Renderer::Submit(lightShader, lightVertexArray, lightTransform);
    
    Renderer::EndScene();*/
}

void ExampleLayer::OnRenderUI()
{
    //editor.OnRender();
}

void ExampleLayer::OnEvent(Candy::Events::Event& e)
{
    //camera.OnEvent(e);
}