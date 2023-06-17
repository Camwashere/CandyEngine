#include "Application.hpp"

#include "GLFW/glfw3.h"
#include <iostream>
#include <mutex>


namespace Candy {
    using namespace Events;
    Application *Application::instance=nullptr;
    
    
    
    Application::Application(const ApplicationData& applicationData) : appData(applicationData), mainWindow(new Window(appData.name, 3000, 1500)), initialized(false), isRunning(false), minimized(false)
    {
        //Engine::Logger::Init();
        CANDY_CORE_ASSERT(!instance, "Application already exists");
        instance = this;
        if (!appData.workingDirectory.empty())
        {
            std::filesystem::current_path(appData.workingDirectory);
        }
        mainWindow->SetEventCallback(CANDY_BIND_EVENT_FUNCTION(Application::OnEvent));
        Graphics::Renderer::Init();
        Graphics::Renderer2D::Init();
        uiLayer = new UILayer();
        PushOverlay(uiLayer);
        
    }
    
    Application::~Application()
    {
        Graphics::Renderer::Shutdown();
    }
    
    void Application::PushLayer(Layer* layer)
    {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Application::PushOverlay(Layer* layer)
    {
        layerStack.PushOverlay(layer);
        layer->OnAttach();
    }
    
    
    void Application::SubmitToMainThread(const std::function<void()>& function)
    {
        std::scoped_lock<std::mutex> lock(mainThreadQueueMutex);
        mainThreadQueue.emplace_back(function);
    }
    
    
    void Application::OnEvent(Events::Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowResize));
        
        for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
        {
            if (event.IsHandled())
            {
                break;
            }
            (*it)->OnEvent(event);
        }
    }
    
    void Application::Run()
    {
        isRunning=true;
        while (isRunning)
        {
            float time = glfwGetTime();
            deltaTime = time-previousFrameTime;
            previousFrameTime = time;
            ExecuteMainThreadQueue();
            
            if (! minimized)
            {
                for (Layer* layer : layerStack)
                {
                    layer->OnUpdate();
                }
                uiLayer->Begin();
                for (Layer* layer : layerStack)
                {
                    layer->OnRenderUI();
                }
                uiLayer->End();
                
            }
            
            mainWindow->OnUpdate();
        }
    }
    
    void Application::Terminate()
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
        if (event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            minimized=true;
            return false;
        }
        minimized=false;
        Graphics::Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
        return true;
    }
    void Application::ExecuteMainThreadQueue()
    {
        std::scoped_lock<std::mutex> lock(mainThreadQueueMutex);
        for (auto& func : mainThreadQueue)
        {
            func();
        }
        mainThreadQueue.clear();
    }
    
    
}
