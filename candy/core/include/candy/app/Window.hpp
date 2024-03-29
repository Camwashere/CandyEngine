#pragma once
#include <cstdint>
#include <string>
#include <CandyPch.hpp>
#include <candy/graphics/GraphicsContext.hpp>
#include <candy/graphics/Renderer.hpp>
#include <candy/event/Events.hpp>


struct GLFWwindow;
namespace Candy::Gum
{
  class Context;
}
namespace Candy
{
    using EventCallbackFunction = std::function<void(Events::Event&)>;
    struct WindowData
    {
        std::string title;
        Math::Vector2i windowSize;
        Math::Vector2i frameBufferSize;
        bool vsync;
        
        
        EventCallbackFunction eventCallback;
        Math::Vector2 mousePos;
        
        
        WindowData(std::string windowTitle, int windowWidth, int windowHeight,
                   bool vsyncEnabled = false) : title(std::move(windowTitle)), windowSize(windowWidth, windowHeight),
                   frameBufferSize(windowWidth, windowHeight), vsync(vsyncEnabled), mousePos(){}
                                                
    public:
        [[nodiscard]] int GetWindowWidth()const{return windowSize.x;}
        [[nodiscard]] int GetWindowHeight()const{return windowSize.y;}
        
        
    };
    class Window
    {
    private:
        WindowData windowData;
        bool fullscreen;
        Graphics::GraphicsContext* graphicsContext;
        //Gum::Context* gumContext;
        
    public:
        GLFWwindow* handle;
    
    private:
        void EventCallbackInit() const;
        void Close() const;
    
    public:
        explicit Window(WindowData data);
        ~Window();
        void StartFrame();
        void EndFrame();
        void SetVSync(bool enabled);
        void OnWindowResize(Events::WindowResizeEvent& event);
        void OnFrameBufferResize(Events::FrameBufferResizeEvent& event);
    
    public:
        void SetEventCallback(const EventCallbackFunction& callback){windowData.eventCallback = callback;}
        void Show() const;
        void Hide() const;
        [[nodiscard]] inline int GetWidth()const{return windowData.GetWindowWidth();}
        [[nodiscard]] inline int GetHeight()const{return windowData.GetWindowHeight();}
        [[nodiscard]] inline bool IsVSyncEnabled()const{return windowData.vsync;}
        //Gum::Context* GetGumContext();
        //Graphics::GraphicsContext& GetGraphicsContext(){return *graphicsContext;}
    
    };
}