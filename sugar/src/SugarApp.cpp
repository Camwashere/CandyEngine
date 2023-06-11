#include <Candy/EntryPoint.hpp>
#include "EditorLayer.hpp"



namespace Candy
{
    using namespace ECS;
    class SugarApp : public Application
    {
    public:
        explicit SugarApp(const ApplicationData& spec) : Application(spec)
        {
            //PushLayer(new ExampleLayer());
            CANDY_CORE_INFO("SugarApp created");
            
            //EditorLayer* layer = new EditorLayer();
            PushLayer(new EditorLayer());
            
            CANDY_CORE_INFO("Editor Layer Pushed");
            
            
            //CANDY_CORE_INFO("Layer Pushed");
        }
        
    };
    
    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        std::cout << "Creating application" << std::endl;
        ApplicationData spec;
        spec.name = "Sugar";
        spec.commandLineArgs = args;
        return new SugarApp(spec);
    }
}