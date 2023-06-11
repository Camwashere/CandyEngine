#include "Renderer.hpp"
#include <iostream>
#include "RenderCommand.hpp"

namespace Candy::Graphics {
        
        UniquePtr<Renderer::SceneData> Renderer::sceneData = CreateUniquePtr<Renderer::SceneData>();
        void Renderer::Init() {
            RenderCommand::Init();
        }
        
        void Renderer::Shutdown() {
            
        }
        
        void Renderer::OnWindowResize(int width, int height) {
            
            RenderCommand::SetViewport(0, 0, width, height);
        }
        void Renderer::BeginScene(OrthographicCamera& camera)
        {
            sceneData->viewMatrix = camera.GetViewMatrix();
            
            
        }
        
        void Renderer::EndScene() {
            
        }
        
        void Renderer::Submit(const SharedPtr<Shader> &shader, const SharedPtr<VertexArray> &vertexArray,
                              const Math::Matrix4 &transform) {
            vertexArray->Bind();
            shader->Bind();
            shader->SetMatrix4("view", sceneData->viewMatrix);
            shader->SetMatrix4("model", transform);
            RenderCommand::DrawIndexed(vertexArray);
            
        }
}