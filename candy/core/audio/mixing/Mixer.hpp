#pragma once

#include "plugins/PluginsAll.hpp"
#include <Candy/CandyEngineBase.hpp>
#include <vector>
namespace Candy::Audio {
    template<typename T>
    concept MixingPluginChild = std::is_base_of<MixingPlugin, T>::value;
    class Mixer
    {
    private:
        std::vector<UniquePtr<MixingPlugin>> processingPlugins;
    public:
        Mixer();
    
    public:
        template<MixingPluginChild T>
        UniquePtr<T> GetPlugin(){}
        
        void Process(float* samples, uint sampleCount);
        
    };
}

