#include "Texture.hpp"
#include "stb_image.h"

namespace Candy::Graphics {
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
                std::cerr << "Failed to load texture" << std::endl;
            }
            
            
        }
        
        Texture::~Texture() {
            glDeleteTextures(1, &rendererID);
        }
        
        
        void Texture::Bind(uint32 slot) const {
            
            glActiveTexture(GL_TEXTURE0+slot);
            glBindTexture(GL_TEXTURE_2D, rendererID);
        }
        
        
        
        SharedPtr<Texture> Texture::Create(const std::string& path)
        {
            return CreateSharedPtr<Texture>(path);
        }
}
