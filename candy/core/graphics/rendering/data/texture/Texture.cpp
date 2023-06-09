#include "Texture.hpp"
#include "stb_image.h"
#include <Candy/Graphics.hpp>



namespace Candy::Graphics {
    
    static GLenum ImageFormatToGLDataFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGB8:  return GL_RGB;
            case ImageFormat::RGBA8: return GL_RGBA;
        }
        
        CANDY_CORE_ASSERT(false);
        return 0;
    }
    
    static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
    {
        switch (format)
        {
            case ImageFormat::RGB8:  return GL_RGB8;
            case ImageFormat::RGBA8: return GL_RGBA8;
        }
        
        CANDY_CORE_ASSERT(false);
        return 0;
    }
        Texture::Texture(const std::string &path){
            
            glGenTextures(1, &rendererID);
            glBindTexture(GL_TEXTURE_2D, rendererID);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
            // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
            int w, h, c;
            unsigned char *data = stbi_load(path.c_str(), &w, &h, &c, 0);
            if (data)
            {
                width = w;
                height = h;
                channels = c;
                filePath = path;
                internalFormat=0;
                dataFormat=0;
                if (channels == 4)
                {
                    internalFormat = GL_RGBA8;
                    dataFormat = GL_RGBA;
                }
                else if (channels == 3)
                {
                    internalFormat = GL_RGB8;
                    dataFormat = GL_RGB;
                }
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                
                
                
                stbi_image_free(data);
            }
            else
            {
                CANDY_CORE_WARN("Failed to load texture: {}", path.c_str());
                //std::cerr << "Failed to load texture" << std::endl;
            }
            
            
        }
        
    
        Texture::Texture(const TextureSpecification& spec)
        : specification(spec), width(spec.width), height(spec.height)
        {
            internalFormat = ImageFormatToGLInternalFormat(specification.format);
            dataFormat = ImageFormatToGLDataFormat(specification.format);
            
            glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
            glTextureStorage2D(rendererID, 1, internalFormat, width, height);
            
            glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        }
        
        Texture::~Texture() {
            glDeleteTextures(1, &rendererID);
        }
        
        
        void Texture::Bind(uint32 slot) const {
            
            glActiveTexture(GL_TEXTURE0+slot);
            glBindTexture(GL_TEXTURE_2D, rendererID);
        }
    
    
    
    bool Texture::operator==(const Texture& other)const
    {
            return rendererID == other.rendererID;
    }
    
    void Texture::SetData(void* data, uint32 size)
    {
            uint32 bpp = dataFormat == GL_RGBA ? 4 : 3;
            CANDY_CORE_ASSERT(size == width * height * bpp, "Data must be entire texture!");
            glTextureSubImage2D(rendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
    }
    
    SharedPtr<Texture> Texture::Create(const TextureSpecification& spec)
    {
            return CreateSharedPtr<Texture>(spec);
    }
    
        
    SharedPtr<Texture> Texture::Create(const std::string& path)
    {
            return CreateSharedPtr<Texture>(path);
    }
}
