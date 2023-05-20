#pragma once
#include "RendererAPI.hpp"

namespace Candy::Graphics {
    class RenderCommand
    {
    private:
        static UniquePtr<RendererAPI> rendererAPI;
    
    public:
        static void Init()
        {
            rendererAPI->Init();
        }
        static void SetViewport(int x, int y, int width, int height)
        {
            rendererAPI->SetViewport(x, y, width, height);
        }
        
        static void SetClearColor(const Color& color)
        {
            rendererAPI->SetClearColor(color);
        }
        
        static void SetRenderingMode(RenderingMode renderingMode)
        {
            rendererAPI->SetRenderingMode(renderingMode);
        }
        
        static void Clear()
        {
            rendererAPI->Clear();
        }
        
        static void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, uint32 indexCount = 0)
        {
            rendererAPI->DrawIndexed(vertexArray, indexCount);
        }
        
        static void DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32 vertexCount)
        {
            rendererAPI->DrawLines(vertexArray, vertexCount);
        }
        
        static void SetLineWidth(float width)
        {
            rendererAPI->SetLineWidth(width);
        }
    };
}

