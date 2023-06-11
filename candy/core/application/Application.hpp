#pragma once

#include "Window.hpp"
#include <Candy/Events.hpp>
#include <Candy/Graphics.hpp>
int main(int argc, char** argv);
namespace Candy {
    
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;
        
        const char* operator[](int index) const
        {
            return Args[index];
        }
    };
    
    struct ApplicationData
    {
        std::string name="Engine Application";
        double version=1.0;
        ApplicationCommandLineArgs commandLineArgs;
    };
    class Application {
    private:
        ApplicationData appData;
        std::shared_ptr<Window> mainWindow;
        
        bool isRunning;
        bool initialized;
        bool minimized;
        float previousFrameTime;
        float deltaTime;
        
        
        
        
        
        
        UILayer* uiLayer;
        LayerStack layerStack;
        std::mutex mainThreadQueueMutex;
        std::vector<std::function<void()>> mainThreadQueue;
    
    private:
        bool OnWindowClose(Events::WindowCloseEvent& event);
        bool OnWindowResize(Events::WindowResizeEvent& event);
        void Run();
        void ExecuteMainThreadQueue();
    
    public:
        Application(const ApplicationData& applicationData);
        ~Application();
    
    public:
        
        void Terminate();
        void OnEvent(Events::Event &event);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        void SubmitToMainThread(const std::function<void()>& function);
        double GetVersion()const{return appData.version;}
        const std::string& GetName()const{return appData.name;}
        const ApplicationData& GetAppData()const{return appData;}
        UILayer* GetUILayer(){return uiLayer;}
    
    public:
        inline static Application &Instance() { return *instance; }
        inline static std::shared_ptr<Window> MainWindowReference() { return instance->mainWindow; }
        inline static float DeltaTime(){return instance->deltaTime;}
        inline static void Close(){instance->Terminate();}
        inline static float AspectRatio(){return (float)instance->mainWindow->GetWidth()/(float)instance->mainWindow->GetHeight();}
        inline static int GetMainWindowWidth(){return instance->mainWindow->GetWidth();}
        inline static int GetMainWindowHeight(){return instance->mainWindow->GetHeight();}
    
    private:
        static Application *instance;
        friend int ::main(int argc, char** argv);
    };
    Application* CreateApplication(ApplicationCommandLineArgs args);
}

