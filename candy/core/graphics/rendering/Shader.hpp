#pragma once

#include <string>
#include "../../../include/Candy/Math.hpp"

#include "../color/ColorAll.hpp"
#include <unordered_map>
#include "data/texture/TextureAll.hpp"
#include "Material.hpp"


namespace Candy::Graphics{
        class Shader {
        private:
            uint32 rendererID;
            std::unordered_map<std::string, int> uniformLocationCache{};
        private:
            bool CheckCompileErrors(uint32 shader, std::string type);
            
            bool CompileShaders(const char *vertexShaderSource, const char *fragmentShaderSource);
        
        public:
            Shader();
            Shader(const char *vertexPath, const char *fragmentPath);
            ~Shader();
        
        public:
            
            bool Initialize(const char *vertexPath, const char *fragmentPath);
            
            void Bind() const;
            
            void Unbind() const;
        
        public:
            
            int SetBool(const std::string &name, bool value);
            
            void SetBool(int id, bool value);
            
            int SetInt(const std::string &name, int value);
            
            void SetInt(int id, int value);
            
            int SetIntArray(const std::string& name, int* values, uint32 count);
            
            void SetIntArray(int id, int* values, uint32 count);
            
            int SetFloat(const std::string &name, float value);
            
            void SetFloat(int id, float value);
            
            int SetFloatArray(const std::string& name, float* values, uint32 count);
            
            void SetFloatArray(int id, float* values, uint32 count);
            
            
            int SetVector2(const std::string &name, const Math::Vector2 &value);
            
            int SetVector2(const std::string &name, float x, float y);
            
            void SetVector2(int id, const Math::Vector2& value);
            
            void SetVector2(int id, float x, float y);
            
            int SetVector3(const std::string &name, const Math::Vector3 &value);
            
            int SetVector3(const std::string &name, float x, float y, float z);
            
            void SetVector3(int id, const Math::Vector3& value);
            
            void SetVector3(int id, float x, float y, float z);
            
            int SetVector4(const std::string &name, const Math::Vector4 &value);
            
            int SetVector4(const std::string &name, float x, float y, float z, float w);
            
            void SetVector4(int id, const Math::Vector4& value);
            
            void SetVector4(int id, float x, float y, float z, float w);
            
            int SetMatrix4(const std::string &name, const Math::Matrix4 &value);
            
            void SetMatrix4(int id, const Math::Matrix4& value);
            
            
            
            int SetColor(const std::string& name, const Color& value);
            
            void SetMaterial(const std::string& name, const Material& value);
            
            void SetLight(const std::string& name, const Light& light);
            
            int PropertyToID(const std::string &name);
            
            uint32 GetRendererID()const{return rendererID;}
            
            static SharedPtr<Shader> Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        };
    
}


