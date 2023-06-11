#pragma once

#include <Candy/CandyEngineBase.hpp>
#include "glad/glad.h"
#include <string>


namespace Candy::Graphics {
        class Texture {
        private:
            uint32 rendererID;
            std::string filePath;
            int width, height, channels;
            uint32 internalFormat, dataFormat;
            
        public:
            bool operator==(const Texture& other)const;
        
        public:
            Texture(const std::string &path);
            Texture(uint32 width, uint32 height);
            ~Texture();
            void SetData(void* data, uint32 size);
            void Bind(uint slot = 0) const;
            void Unbind() const;
            inline int GetWidth() const { return width; }
            inline int GetHeight() const { return height; }
            inline int GetSizeInPixels()const{return width*height;}
            inline uint GetRendererID()const{return rendererID;}
            inline int GetChannels() const { return channels; }
            inline const std::string& GetPath()const{return filePath;}
            
            
            
            static SharedPtr<Texture> Create(uint32 width, uint32 height);
            static SharedPtr<Texture> Create(const std::string& path);
            
        };
}


