#include <candy/app/Application.hpp>
#include <ranges>
//#include <Candy/Graphics.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <GLFW/glfw3.h>
#include <candy/graphics/RenderCommand.hpp>
#include <CandyEngine.hpp>
#include <candy/project/ProjectManager.hpp>
#include <gum/Context.hpp>
#include <gum/event/EventType.hpp>
#include <gum/event/EventDispatcher.hpp>
#include <gum/event/MouseEvent.hpp>

namespace Candy
{
  static void GLFWErrorCallback(int error, const char* description)
  {
    CANDY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
  }
  
  using namespace Events;
  using namespace Graphics;
  using namespace Math;
  Application* Application::instance = nullptr;
  
  Application::Application(ApplicationData applicationData) : appData(std::move(applicationData)), isRunning(false), minimized(false)
  {
    CANDY_PROFILE_BEGIN_SESSION("Candy Startup", "profiling/Startup.json");
    CANDY_PROFILE_FUNCTION();
    Log::Init();
    CANDY_CORE_INFO("Initializing Candy Engine");
    CandyEngine::Init();
    
    
    CANDY_CORE_INFO("Initialized Candy Engine");
    CANDY_CORE_ASSERT(!instance, "Application already exists");
    instance = this;
    
    InitGLFW();
    
    mainWindow = CreateUniquePtr<Window>(WindowData(ProjectManager::ProjectName(), 3000, 1500));
    mainWindow->SetEventCallback(CANDY_BIND_EVENT_FUNCTION(Application::OnEvent));
    
    
    uiLayer = new UILayer();
    PushOverlay(uiLayer);
    
    gumLayer = new GumLayer(mainWindow->GetGumContext());
    PushOverlay(gumLayer);
    
    
  }
  
  void Application::InitGLFW()
  {
    int success = glfwInit();
    CANDY_CORE_ASSERT(success, "FAILED TO INITIALIZE GLFW");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    
    int widthMM, heightMM;
    glfwGetMonitorPhysicalSize(primaryMonitor, &widthMM, &heightMM);
    
    float contentScaleX, contentScaleY;
    glfwGetMonitorContentScale(primaryMonitor, &contentScaleX, &contentScaleY);
    
    const auto scaleX = static_cast<float>(contentScaleX);
    const auto scaleY = static_cast<float>(contentScaleY);
    
    double widthInches = (widthMM / 25.4) * scaleX;  // Adjust width to take into account OS scaling
    double heightInches = (heightMM / 25.4) * scaleY;  // Adjust height for OS scaling
    
    double diagonalSizeInches = sqrt(widthInches * widthInches + heightInches * heightInches);
    double diagonalSizePixels = sqrt( (mode->width * scaleX) * (mode->width * scaleX) + (mode->height * scaleY) * (mode->height * scaleY) );  // Adjust pixel dimensions for OS scaling
    
    double PPI = diagonalSizePixels / diagonalSizeInches;
    
    pixelsPerInch = static_cast<float>(PPI);
    pixelsPerPoint = pixelsPerInch / 72.0f;
    
    screenSizeInPixels = Vector2(static_cast<float>(mode->width) * scaleX, static_cast<float>(mode->height) * scaleY);  // Adjust screen size in pixels for OS scaling
    
    screenSizeInPoints = screenSizeInPixels / pixelsPerPoint;
    
    glfwSetErrorCallback(GLFWErrorCallback);
  }
  void Application::Run()
  {
    isRunning = true;
    
    instance->mainWindow->Show();
    
    CANDY_PROFILE_END_SESSION();
    CANDY_PROFILE_BEGIN_SESSION("Candy Runtime", "profiling/Runtime.json");
    while (isRunning)
    {
      Update();
      
    }
    CANDY_PROFILE_END_SESSION();
    CANDY_PROFILE_BEGIN_SESSION("Candy Shutdown", "profiling/Shutdown.json");
    CleanUp();
    CANDY_PROFILE_END_SESSION();
    
  }
  
  void Application::Update()
  {
    CANDY_PROFILE_FUNCTION();
    PollEvents();
    mainWindow->StartFrame();
    
    for (Layer* layer: layerStack)
    {
      layer->OnUpdate();
    }
    
    gumLayer->Begin();
    for (Layer* layer: layerStack)
    {
      layer->OnRenderGum();
    }
    gumLayer->End();
    
    uiLayer->Begin();
    for (Layer* layer: layerStack)
    {
      layer->OnRenderUI();
    }
    uiLayer->End();
    
    mainWindow->EndFrame();
  }
  
  void Application::PollEvents()
  {
    frameTime.Update();
    glfwPollEvents();
  }
  
  void Application::CleanUp()
  {
    CANDY_PROFILE_FUNCTION();
    
    for (Layer* layer: std::ranges::reverse_view(layerStack))
    {
      layer->OnDetach();
    }
    Vulkan::Shutdown();
    
    glfwTerminate();
  }
  
  void Application::Close()
  {
    isRunning = false;
    
  }
  void Application::OnEvent(Events::Event& event)
  {
    CANDY_PROFILE_FUNCTION();
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnWindowResize));
    dispatcher.Dispatch<FrameBufferResizeEvent>(CANDY_BIND_EVENT_FUNCTION(Application::OnFrameBufferResize));
    
    for (auto& it: std::ranges::reverse_view(layerStack))
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
  
  
  UILayer& Application::GetUILayer()
  {
    return *instance->uiLayer;
  }
  GumLayer& Application::GetGumLayer()
  {
    return *instance->gumLayer;
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
  
  
  float Application::PixelsPerInch()
  {
    return instance->pixelsPerInch;
  }
  float Application::PixelsPerPoint()
  {
    return instance->pixelsPerPoint;
  }
  Math::Vector2 Application::ScreenSizeInPoints()
  {
    return instance->screenSizeInPoints;
  }
  Math::Vector2 Application::ScreenSizeInPixels()
  {
    return instance->screenSizeInPixels;
  }
  float Application::AverageFPS()
  {
    return instance->frameTime.GetAverageFPS();
  }
  void Application::Shutdown()
  {
    instance->Close();
  }
  bool Application::OnWindowClose(Events::WindowCloseEvent& event)
  {
    isRunning = false;
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
  
  void Matrix4InverseTest(const Matrix4& mat, int iterations = 10)
  {
    CANDY_PROFILE_FUNCTION();
    for (int i = 0; i < iterations; i++)
    {
      Matrix4::Inverse(mat);
    }
  }
  
  void Matrix4FastInverseTest(const Matrix4& mat, int iterations = 10)
  {
    CANDY_PROFILE_FUNCTION();
    for (int i = 0; i < iterations; i++)
    {
      
      Matrix4::FastInverse(mat);
    }
  }
  void Matrix4Tests(int iterations = 1)
  {
    CANDY_PROFILE_FUNCTION();
    for (int i = 0; i < iterations; i++)
    {
      Matrix4 mat = Matrix4::Random(0.0f, 50.0f);
      Matrix4InverseTest(mat, 10);
      Matrix4FastInverseTest(mat, 10);
    }
    
  }
  void Application::RunTests()
  {
    CANDY_PROFILE_END_SESSION();
    CANDY_PROFILE_BEGIN_SESSION("Candy Tests", "profiling/Tests.json");
    Matrix4Tests(50);
    CANDY_PROFILE_END_SESSION();
  }
  
  
}