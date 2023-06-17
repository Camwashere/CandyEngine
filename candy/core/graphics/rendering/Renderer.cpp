#include "Renderer.hpp"
#include <iostream>
#include "RenderCommand.hpp"
#include "Renderer2D.hpp"
namespace Candy::Graphics {
        
        UniquePtr<Renderer::SceneData> Renderer::sceneData = CreateUniquePtr<Renderer::SceneData>();
        void Renderer::Init() {
            RenderCommand::Init();
            Renderer2D::Init();
        }
        
        void Renderer::Shutdown() {
            Renderer2D::Shutdown();
            
        }
        
        void Renderer::OnWindowResize(int width, int height) {
            
            RenderCommand::SetViewport(0, 0, width, height);
        }
        void Renderer::BeginScene(OrthographicCamera& camera)
        {
            sceneData->viewMatrix = camera.GetViewProjectionMatrix();
            
            
        }
        
        void Renderer::EndScene() {
            
        }
        
        void Renderer::Submit(const SharedPtr<Shader> &shader, const SharedPtr<VertexArray> &vertexArray,
                              const Math::Matrix4 &transform) {
            shader->Bind();
            shader->SetMatrix4("u_ViewProjection", sceneData->viewMatrix);
            shader->SetMatrix4("u_Transform", transform);
            vertexArray->Bind();
            RenderCommand::DrawIndexed(vertexArray);
            
        }
}