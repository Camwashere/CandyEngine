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
            PushLayer(new EditorLayer());
        }
        
    };
    
    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationData spec;
        spec.name = "Sugar";
        spec.commandLineArgs = args;
        return new SugarApp(spec);
    }
}