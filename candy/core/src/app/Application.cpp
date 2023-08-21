#include <candy/app/Application.hpp>
#include <ranges>
//#include <Candy/Graphics.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <GLFW/glfw3.h>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy
{
    using namespace Events;
    using namespace Graphics;
    using namespace Math;
    Application* Application::instance = nullptr;
    
    Application::Application(ApplicationData  applicationData) : appData(std::move(applicationData)), isRunning(false), minimized(false)//, uiLayer(nullptr)
    {
        CANDY_PROFILE_FUNCTION();
        Log::Init();
        CANDY_CORE_ASSERT(!instance, "Application already exists");
        instance=this;
        if (!appData.workingDirectory.empty())
        {
            std::filesystem::current_path(appData.workingDirectory);
        }
        
        mainWindow = CreateUniquePtr<Window>(WindowData(appData.name, 3000, 1500));
        
        mainWindow->SetEventCallback(CANDY_BIND_EVENT_FUNCTION(Application::OnEvent));
        
        RenderCommand::Init();
      uiLayer = new UILayer();
      PushOverlay(uiLayer);
      
      //mainWindow->GetGraphicsContext().RecreateTarget();
      
    }
    
    
    
    void Application::OnEvent(Events::Event &event)
    {
        CANDY_PROFILE_FUNCTION();
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowResize));
        dispatcher.Dispatch<FrameBufferResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnFrameBufferResize));
      
      for (auto& it : std::ranges::reverse_view(layerStack))
      {
        if (event.IsHandled())
        {
          break;
        }
        it->OnEvent(event);
      }
    }
  
  
  void Application::PushLayer(Layer* layer)
  {
      CANDY_PROFILE_FUNCTION();
      layerStack.PushLayer(layer);
      layer->OnAttach();
  }
  void Application::PushOverlay(Layer* layer)
  {
      CANDY_PROFILE_FUNCTION();
      layerStack.PushOverlay(layer);
      layer->OnAttach();
  }
  
  void Application::UpdateLayers()
  {
      CANDY_PROFILE_FUNCTION();
      for (Layer* layer : layerStack)
      {
        layer->OnUpdate();
      }
  }
  UILayer& Application::GetUILayer()
  {
      return *instance->uiLayer;
  }
  float Application::DeltaTime()
  {
      return instance->frameTime.GetDeltaTime();
  }
  
  float Application::CurrentTime()
  {
      return instance->frameTime.GetCurrentTime();
  }
  float Application::FPS()
  {
      return instance->frameTime.GetFPS();
  }
    void Application::Shutdown()
    {
        instance->Close();
    }
    void Application::Run()
    {
        CANDY_PROFILE_FUNCTION();
        isRunning=true;
        Renderer::Start();
        while(isRunning)
        {
          frameTime.Update();
          UpdateLayers();
          uiLayer->Begin();
          for (Layer* layer : layerStack)
          {
            layer->OnRenderUI();
          }
          uiLayer->End();
          mainWindow->OnUpdate();
        }
        CleanUp();
        
    }
    
    void Application::CleanUp()
    {
      //CANDY_CORE_INFO("STARTED APPLICATION CLEANUP");
      
      for (Layer *layer: std::ranges::reverse_view(layerStack))
      {
        layer->OnDetach();
      }
      Vulkan::Shutdown();
      
      glfwTerminate();
      CANDY_CORE_INFO("TERMINATED GLFW");
      
      
    }
    
    void Application::Close()
    {
        isRunning=false;
        
    }
    
    bool Application::OnWindowClose(Events::WindowCloseEvent& event)
    {
        isRunning=false;
        return true;
    }
    
    bool Application::OnWindowResize(Events::WindowResizeEvent& event)
    {
        CANDY_PROFILE_FUNCTION();
        if (event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            minimized = true;
            return false;
        }
        minimized = false;
        mainWindow->OnWindowResize(event);
        
        return false;
    }
  
  bool Application::OnFrameBufferResize(Events::FrameBufferResizeEvent& event)
  {
      CANDY_PROFILE_FUNCTION();
      mainWindow->OnFrameBufferResize(event);
      return false;
  }
    
    
}