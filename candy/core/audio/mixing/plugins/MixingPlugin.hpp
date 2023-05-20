#pragma once

#include <Candy/CandyEngineBase.hpp>
#include <functional>
namespace Candy::Audio {
    // processOutputSamples = std::bind(&MixingPlugin::DummyBaseProcessOutputFunc, this, std::placeholders::_1, std::placeholders::_2);
    class MixingPlugin
    {
    protected:
        bool active;
        std::function<void(float* samples, uint sampleCount)> processOutputSamples;
    
    protected:
        MixingPlugin(const std::function<void(float* samples, uint sampleCount)>& outputFunc) : processOutputSamples(outputFunc){}
    
    public:
        void ProcessOutputSamples(float* samples, uint sampleCount){processOutputSamples(samples, sampleCount);}
        bool IsActive()const{return active;}
        void SetActive(bool isActive){active=isActive;}
    };
}

