#include "AudioManager.hpp"
#include <portaudio.h>
#include <cstring>
#include <Candy/Math.hpp>
#include "mixing/plugins/PluginsAll.hpp"




namespace Candy::Audio {
    AudioManager::AudioManager()
    {
        
        if (Pa_Initialize()==paNoError)
        {
            std::cout << "Successfully initialized portaudio" << std::endl;
            std::cout << "Portaudio Version: " << Pa_GetVersion() << std::endl;
        }
        else
        {
            std::cout << "Failed to initialize portaudio" << std::endl;
        }
        
        //mixer.AddPlugin(VolumePlugin());
        
        
    }
    AudioManager::~AudioManager()
    {
        Pa_Terminate();
    }
    struct UserData{
        int frameIndex;
        int maxFrameIndex;
        int numChannels;
        SNDFILE* file;
    };
    
    
    void AudioManager::ReadFile(const std::string& filePath)
    {
        /*SF_INFO fileInfo;
        memset(&fileInfo, 0, sizeof(fileInfo));
        SNDFILE* file = sf_open(filePath.c_str(), SFM_READ, &fileInfo);
        if (file)
        {
            std::cout << "Successfully opened file" << std::endl;
        }
        else
        {
            std::cerr << "Could not open file" << std::endl;
        }
        
        
        PlayFile(file, &fileInfo);
        sf_close(file);*/
        
    }
    
    int output_cb(const void * input, void * output, unsigned long frames_per_buffer,
                         const PaStreamCallbackTimeInfo *time_info,
                         PaStreamCallbackFlags flags, void * data)
    {
        /*UserData* userData = static_cast<UserData*>(data);
        
        float* out = static_cast<float*>(output);
        
        
        userData->frameIndex += frames_per_buffer;
        
        
        sf_count_t count = sf_readf_float(userData->file, out, frames_per_buffer);
        int outputSize = count * userData->numChannels;
        
        
        float min = Math::MAX_FLOAT;
        float max = Math::MIN_FLOAT;
        
        for(int i=0; i<outputSize; i++)
        {
            min = Math::Min(min, out[i]);
            max = Math::Max(max, out[i]);
            //out[i] *= Math::Sin(time_info->currentTime);
        }
        float difference = max-min;
        float targetMin = -0.2f;
        float targetMax = 0.2f;
        float targetDifference=targetMax-targetMin;
        float compressionAmount = 0.8f;
        time_info->currentTime;
        
        
        
        
        float volumeDecrease=0.2f;
        for (int i=0; i<outputSize; i++)
        {
            float compressed = (out[i]-min)*(compressionAmount/difference);
            out[i] = compressed; // (Math::Sin(time_info->currentTime)*volumeDecrease);
            
        }
        
        if (userData->frameIndex < userData->maxFrameIndex)
        {
            return paContinue;
        }
        return 1;*/
        
    }
    
    void AudioManager::PlayFile(SNDFILE* file, SF_INFO* fileInfo)
    {
        /*PaStreamParameters outputParameters;
        PaStream* stream;
        PaError err = paNoError;
        
        int totalSamples = fileInfo->samplerate*fileInfo->frames;
        UserData* userData = new UserData(0, fileInfo->frames, fileInfo->channels, file);
        
        //memset(userData.recordedSamples, 0, totalSamples);
        
        
        
        
        
        
        outputParameters.device = Pa_GetDefaultOutputDevice();
        if (outputParameters.device == paNoDevice)
        {
            std::cerr << "Error, no default output device" << std::endl;
            return;
        }
        
        
        outputParameters.channelCount = fileInfo->channels;
        outputParameters.sampleFormat = paFloat32;
        int sampleRate = 44100;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        
        
        
        err = Pa_OpenStream(&stream, NULL, &outputParameters, fileInfo->samplerate, paFramesPerBufferUnspecified, 0, output_cb, userData);
        if (err != paNoError)
        {
            std::cerr << "Failed to open stream" << std::endl;
            return;
        }
        err = Pa_StartStream(stream);
        if (err != paNoError)
        {
            std::cerr << "Failed to start stream" << std::endl;
        }
        
        while (Pa_IsStreamActive(stream) != paNoError)
        {
        
        }
        Pa_StopStream(stream);
        
        
        err = Pa_CloseStream(stream);
        if (err != paNoError)
        {
            std::cerr << "Failed to close stream" << std::endl;
        }*/
        
        
    }
}