#pragma once

#include <CandyPch.hpp>
#include "Window.hpp"
#include <candy/utils/FrameTime.hpp>
#include "LayerStack.hpp"
#include <candy/ui/UILayer.hpp>
#include <candy/ui/GumLayer.hpp>
#include <candy/utils/Version.hpp>
#include "candy/project/Project.hpp"
int main(int argc, char **argv);

namespace Candy
{
  struct ApplicationCommandLineArgs
  {
    int count = 0;
    char **args = nullptr;
    
    const char *operator[](std::size_t index) const {return args[index];}
  };
  
  struct ApplicationData
  {
    std::string name = "Candy Application";
    Version version = Version(1, 0, 0);
    std::string workingDirectory;
    ApplicationCommandLineArgs commandLineArgs;
  };
  
  class Application
  {
  private:
    ApplicationData appData;
    UniquePtr<Window> mainWindow;
    float pixelsPerInch;
    float pixelsPerPoint;
    Math::Vector2 screenSizeInPoints;
    Math::Vector2 screenSizeInPixels;
    
    bool isRunning;
    bool minimized;
    FrameTime frameTime;
    UILayer* uiLayer;
    //GumLayer* gumLayer;
    LayerStack layerStack;
  
  private:
    bool OnWindowClose(Events::WindowCloseEvent &event);
    bool OnWindowResize(Events::WindowResizeEvent &event);
    bool OnFrameBufferResize(Events::FrameBufferResizeEvent& event);
    
    void InitGLFW();
    
    void PollEvents();
    void Run();
    void Update();
    void Close();
    void CleanUp();
  
  public:
    explicit Application(ApplicationData applicationData);
    ~Application()=default;
  
  public:
    void OnEvent(Events::Event &event);
    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);
  
  
  public:
    static void RunTests();
    //static GumLayer& GetGumLayer();
    static inline Window &GetMainWindowReference() {return *instance->mainWindow;}
    static Application &Instance() {return *instance;}
    static float DeltaTime();
    static float CurrentTime();
    static float FPS();
    static float AverageFPS();
    static void Shutdown();
    static float PixelsPerInch();
    static float PixelsPerPoint();
    static Math::Vector2 ScreenSizeInPoints();
    static Math::Vector2 ScreenSizeInPixels();
  
  private:
    static Application *instance;
    friend int::main(int argc, char **argv);
  };
}