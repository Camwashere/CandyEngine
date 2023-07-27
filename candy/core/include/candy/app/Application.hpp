#pragma once
#include <CandyPch.hpp>
#include "Window.hpp"
#include <candy/utils/FrameTime.hpp>
#include "LayerStack.hpp"
int main(int argc, char** argv);
namespace Candy
{
    struct ApplicationCommandLineArgs
    {
        int count = 0;
        char **args = nullptr;
        
        const char *operator[](std::size_t index) const
        { return args[index]; }
    };
    
    struct ApplicationData
    {
        std::string name = "Candy Application";
        double version = 1.0;
        std::string workingDirectory;
        ApplicationCommandLineArgs commandLineArgs;
    };
    class Application
    {
    private:
        ApplicationData appData;
        UniquePtr<Window> mainWindow;
        bool isRunning;
        bool minimized;
        FrameTime frameTime;
        LayerStack layerStack;
        
    private:
        bool OnWindowClose(Events::WindowCloseEvent& event);
        bool OnWindowResize(Events::WindowResizeEvent& event);
        void Run();
        void Close();
        void CleanUp();
        
    public:
        explicit Application(ApplicationData  applicationData);
        ~Application();
        
    public:
        void OnEvent(Events::Event& event);
      void PushLayer(Layer* layer);
      void PushOverlay(Layer* layer);
      void UpdateLayers();
      
        
    public:
        static inline Window& GetMainWindowReference(){return *instance->mainWindow;}
        static Application& Instance(){return *instance;}
        static float DeltaTime();
        static float CurrentTime();
      static void Shutdown();
    
    private:
        static Application* instance;
        friend int ::main(int argc, char** argv);
    };
}