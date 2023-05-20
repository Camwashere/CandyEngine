#pragma once

#include <Candy/CandyEngineBase.hpp>
#include "../color/ColorAll.hpp"
#include "data/VertexArray.hpp"
#include "data/RenderingMode.hpp"
namespace Candy::Graphics {
    class RendererAPI
    {
    public:
        enum class API
        {
            None=0,
            OpenGL=1,
        };
    
    private:
        static API CurrentAPI;
    
    public:
        void Init();
        void SetViewport(int x, int y, int width, int height);
        void SetRenderingMode(RenderingMode renderingMode);
        void SetClearColor(const Color& color);
        void Clear();
        void DrawIndexed(const SharedPtr<VertexArray>& vertexArray, uint32 indexCount=0);
        void DrawLines(const SharedPtr<VertexArray>& vertexArray, uint32 vertexCount);
        void SetLineWidth(float width);
        static API GetAPI(){return CurrentAPI;}
        static UniquePtr<RendererAPI> Create();
    };
}

