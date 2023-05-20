#pragma once
#include <Candy/CandyEngineBase.hpp>
#include "mixing/Mixer.hpp"
#include <sndfile.h>
namespace Candy::Audio{
    class AudioManager
    {
    private:
        Mixer mixer;
    public:
        AudioManager();
        ~AudioManager();
    
    public:
        void ReadFile(const std::string& filePath);
        void PlayFile(SNDFILE* file, SF_INFO* fileInfo);
        
    };
}