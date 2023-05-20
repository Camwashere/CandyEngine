#include "VolumePlugin.hpp"

namespace Candy::Audio {
    
    void VolumePlugin::ProcessVolume(float *samples, uint sampleCount) {
        for (int i=0; i<sampleCount; i++)
        {
            samples[i] *= volumeMultiplier;
        }
        
    }
    
    VolumePlugin::VolumePlugin() : MixingPlugin(std::bind(&VolumePlugin::ProcessVolume, this, std::placeholders::_1, std::placeholders::_2)), volumeMultiplier(1.0f){
    
    }
    VolumePlugin::VolumePlugin(float volume) : MixingPlugin(std::bind(&VolumePlugin::ProcessVolume, this, std::placeholders::_1, std::placeholders::_2)), volumeMultiplier(volume){
    
    }
}