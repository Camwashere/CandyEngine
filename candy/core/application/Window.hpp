#pragma once

#include <string>
#include "../../include/Candy/Math.hpp"
#include "../../include/Candy/Graphics.hpp"

struct GLFWwindow;
namespace Candy {
    using EventCallbackFunction = std::function<void(Events::Event&)>;
    struct WindowData {
        std::string title;
        int width, height;
        bool vsync;
        EventCallbackFunction eventCallback;
        Math::Vector2 mousePos;
        
        WindowData(const std::string &windowTitle, int windowWidth, int windowHeight,
                   bool vsyncEnabled = false) : title(windowTitle), width(windowWidth), height(windowHeight),
                                                vsync(vsyncEnabled), mousePos() {}
    };
    
    class Window {
    private:
        UniquePtr<Graphics::GraphicsContext> graphicsContext;
        WindowData windowData;
    
    private:
        void Init();
    public:
        
        
        bool fullscreen;
        GLFWwindow *ref;
    public:
        static Window *instance;
    
    private:
        void Shutdown();
    
    public:
        Window(const std::string &name, int windowWidth, int windowHeight);
        
        Window(const WindowData &data);
        
        ~Window();
        
        void OnUpdate();
        
        void SetVSync(bool enabled);
    
    public:
        void SetEventCallback(const EventCallbackFunction& callback) {windowData.eventCallback = callback;}
        
        inline int GetWidth() const { return windowData.width; }
        
        inline int GetHeight() const { return windowData.height; }
        
        
    };
}


