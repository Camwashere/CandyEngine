#pragma once

#include <Candy/CandyEngineBase.hpp>
#include "glad/glad.h"
#include <string>


namespace Candy::Graphics {
    
        enum class ImageFormat
        {
            None = 0,
            R8,
            RGB8,
            RGBA8,
            RGBA32F
        };
        
        struct TextureSpecification
        {
            uint32 width=1;
            uint32 height=1;
            ImageFormat format=ImageFormat::RGBA8;
            bool generateMips=true;
        };
        
        
        class Texture {
        private:
            TextureSpecification specification;
            uint32 rendererID;
            std::string filePath;
            bool isLoaded;
            uint32_t width, height, channels;
            uint32 internalFormat, dataFormat;
            
        public:
            bool operator==(const Texture& other)const;
        
        public:
            Texture(const std::string &path);
            //Texture(uint32 width, uint32 height);
            Texture(const TextureSpecification& spec);
            ~Texture();
            void SetData(void* data, uint32 size);
            void Bind(uint slot = 0) const;
            void Unbind() const;
            inline uint32 GetWidth() const { return width; }
            inline uint32 GetHeight() const { return height; }
            inline int GetSizeInPixels()const{return width*height;}
            inline uint GetRendererID()const{return rendererID;}
            inline uint32 GetChannels() const { return channels; }
            inline const std::string& GetPath()const{return filePath;}
            
            
            
            static SharedPtr<Texture> Create(const TextureSpecification& spec);
            static SharedPtr<Texture> Create(const std::string& path);
            
        };
}


