#include <Candy/CandyEngine.hpp>
#include <Candy/EntryPoint.hpp>
#include "EditorLayer.hpp"
#include <ExampleLayer.hpp>
namespace Candy
{
    class SugarApp : public Application
    {
    public:
        SugarApp(const ApplicationData& spec) : Application(spec)
        {
            PushLayer(new ExampleLayer());
            //PushLayer(new EditorLayer());
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