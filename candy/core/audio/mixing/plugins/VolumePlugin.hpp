#pragma once
#include "MixingPlugin.hpp"

namespace Candy::Audio {
    class VolumePlugin : public MixingPlugin
    {
    private:
        float volumeMultiplier;
    private:
        void ProcessVolume(float* samples, uint sampleCount);
    public:
        VolumePlugin();
        VolumePlugin(float volume);
    };
}
