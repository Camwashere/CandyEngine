#include <Candy/CandyEngineCore.hpp>
#include "sandbox/ExampleLayer.hpp"
#include <filesystem>

int main(int argc, char** argv)
{
    
    auto app = Candy::Application({"Candy Engine", 1.0, {argc, argv}});
    auto* layer = new ExampleLayer();
    app.PushLayer(layer);
    app.Run();
    
    
    return 0;
}