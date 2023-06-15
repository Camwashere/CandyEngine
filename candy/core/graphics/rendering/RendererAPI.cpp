#include "RendererAPI.hpp"
#include "GraphicsContext.hpp"
#include <Candy/App.hpp>
namespace Candy::Graphics{
    RendererAPI::API RendererAPI::CurrentAPI=RendererAPI::API::OpenGL;
    
    void OpenGLMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char* message,
            const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         CANDY_CORE_CRITICAL(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       CANDY_CORE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          CANDY_CORE_WARN(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: CANDY_CORE_TRACE(message); return;
        }
        
        CANDY_CORE_ASSERT(false, "Unknown severity level!");
    }
    
    void RendererAPI::Init() {
    #ifdef CANDY_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    #endif
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
    }
    void RendererAPI::SetViewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }
    void RendererAPI::SetRenderingMode(RenderingMode renderingMode)
    {
        switch(renderingMode)
        {
            case DEFAULT:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            case WIREFRAME:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
        }
    }
    void RendererAPI::SetClearColor(const Color &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    void RendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void RendererAPI::DrawIndexed(const SharedPtr<VertexArray> &vertexArray, uint32 indexCount) {
        vertexArray->Bind();
        uint32 count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }
    void RendererAPI::DrawLines(const SharedPtr<VertexArray> &vertexArray, uint32 vertexCount) {
        vertexArray->Bind();
        glDrawArrays(GL_LINES, 0, vertexCount);
    }
    void RendererAPI::SetLineWidth(float width) {
        glLineWidth(width);
    }
    
    UniquePtr<RendererAPI> RendererAPI::Create(){
        return CreateUniquePtr<RendererAPI>();
    }
}