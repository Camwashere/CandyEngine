#include "Mixer.hpp"
namespace Candy::Audio {
    Mixer::Mixer(){}
    
    
    void Mixer::Process(float* samples, uint sampleCount)
    {
        for (int i=0; i<processingPlugins.size(); i++)
        {
            processingPlugins[i]->ProcessOutputSamples(samples, sampleCount);
        }
    }
}