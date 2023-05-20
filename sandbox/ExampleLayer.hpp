#pragma once

#include <Candy/CandyEngine.hpp>
#include "ChunkRenderer.hpp"

class ExampleLayer : public Candy::Layer
{

private:
    Candy::SharedPtr<Candy::Graphics::Shader> shader;
    Candy::SharedPtr<Candy::Graphics::Shader> lightShader;
    Candy::SharedPtr<Candy::Graphics::VertexArray> vertexArray;
    Candy::SharedPtr<Candy::Graphics::VertexArray> lightVertexArray;
    Candy::Graphics::Camera camera;
    Candy::SharedPtr<Candy::Graphics::Texture> texture1;
    Candy::SharedPtr<Candy::Graphics::Texture> texture2;
    Candy::Graphics::Material material;
    Candy::Graphics::Light light;
    ChunkRenderer chunkRenderer;
    
    Candy::UI::EditorLayout editor;



private:
    void CreateShaderResources();
    void InitializePrimaryShader(const Candy::Graphics::Mesh& mesh);
    void InitializeLightingShader(const Candy::Graphics::Mesh& mesh);

public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;
    
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    
    void OnUpdate() override;
    void OnRenderUI()override;
    
    void OnEvent(Candy::Events::Event& e) override;
    
    
    
    
    
    
};

