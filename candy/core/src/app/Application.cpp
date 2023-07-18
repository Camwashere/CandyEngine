#include <candy/app/Application.hpp>
#include <ranges>
//#include <Candy/Graphics.hpp>
namespace Candy
{
    using namespace Events;
    //using namespace Graphics;
    using namespace Math;
    Application* Application::instance = nullptr;
    
    Application::Application(ApplicationData  applicationData) : appData(std::move(applicationData)), isRunning(false), minimized(false)
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
        
        
        
        
    }
    
    Application::~Application()
    {
        CANDY_PROFILE_FUNCTION();
        
        //Renderer::Shutdown();
    }
    
    void Application::OnEvent(Events::Event &event)
    {
        CANDY_PROFILE_FUNCTION();
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowResize));
        
        /*for (auto& it : std::ranges::reverse_view(layerStack))
        {
            if (event.IsHandled())
            {
                break;
            }
            it->OnEvent(event);
        }*/
    }
  
  float Application::DeltaTime()
  {
      return instance->frameTime.GetDeltaTime();
  }
  
  float Application::CurrentTime()
  {
      return instance->frameTime.GetCurrentTime();
  }
    void Application::Shutdown()
    {
        instance->Close();
    }
    void Application::Run()
    {
        CANDY_PROFILE_FUNCTION();
        isRunning=true;
        
        while(isRunning)
        {
          frameTime.Update();
          mainWindow->OnUpdate();
        }
        CleanUp();
    }
    
    void Application::CleanUp()
    {
    
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
        
        //Renderer::OnWindowResize((int)event.GetWidth(), (int)event.GetHeight());
        return false;
    }
    
    
}