#pragma once

#include "data/VertexArray.hpp"
#include "data/IndexBuffer.hpp"
#include "Shader.hpp"
#include "RendererAPI.hpp"
#include "camera/CameraAll.hpp"
namespace Candy::Graphics{
        class Renderer {
        private:
            struct SceneData
            {
                Math::Matrix4 viewMatrix;
            };
            static UniquePtr<SceneData> sceneData;
        public:
            static void Init();
            static void Shutdown();
            static void OnWindowResize(int width, int height);
            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();
            static void Submit(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertexArray, const Math::Matrix4& transform=Math::Matrix4::Identity);
            static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}
        };
}





