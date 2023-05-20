#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"
#include "../../../include/Candy/Graphics.hpp"

namespace Candy::Graphics{
        
        
        Shader::Shader() {}
        
        Shader::Shader(const char *vertexPath, const char *fragmentPath) {
            Initialize(vertexPath, fragmentPath);
        }
        Shader::~Shader()
        {
            glDeleteProgram(rendererID);
        }
        
        bool Shader::Initialize(const char *vertexPath, const char *fragmentPath) {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // close file handlers
                vShaderFile.close();
                fShaderFile.close();
                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure e) {
                std::cerr << "ERROR::SHADER::FILE NOT SUCCESSFULLY READ" << std::endl;
                return false;
            }
            if (!CompileShaders(vertexCode.c_str(), fragmentCode.c_str()))
            {
                std::cerr << "ERROR::SHADER::FAILED TO COMPILE SHADERS" << std::endl;
                return false;
            }
            
            
            return true;
        }
        
        bool Shader::CompileShaders(const char *vertexShaderCode, const char *fragmentShaderCode) {
            uint32 vertex, fragment;
            
            
            // vertex Shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexShaderCode, NULL);
            glCompileShader(vertex);
            if (!CheckCompileErrors(vertex, "VERTEX"))
            {
                std::cerr << "Failed to compile vertex shader!" << std::endl;
                return false;
            }
            // print compile errors if any
            
            
            // Fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
            glCompileShader(fragment);
            if (!CheckCompileErrors(fragment, "FRAGMENT"))
            {
                std::cerr << "Failed to compile fragment shader!" << std::endl;
                return false;
            }
            
            // print compile errors if any
            
            
            // shader Program
            rendererID = glCreateProgram();
            glAttachShader(rendererID, vertex);
            glAttachShader(rendererID, fragment);
            glLinkProgram(rendererID);
            if (!CheckCompileErrors(rendererID, "PROGRAM"))
            {
                std::cerr << "Failed to compile shader program!" << std::endl;
                return false;
            }
            
            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return true;
        }
        
        bool Shader::CheckCompileErrors(GLuint shader, std::string type) {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                              << "\n -- --------------------------------------------------- -- " << std::endl;
                    return false;
                }
            } else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                              << "\n -- --------------------------------------------------- -- " << std::endl;
                    return false;
                }
            }
            return true;
        }
        
        void Shader::Bind() const {
            glUseProgram(rendererID);
        }
        
        void Shader::Unbind() const {
            glUseProgram(0);
        }
        
        int Shader::SetBool(const std::string &name, bool value) {
            int id = PropertyToID(name);
            glUniform1i(id, (int) value);
            return id;
        }
        
        void Shader::SetBool(int id, bool value){
            glUniform1i(id, (int)value);
        }
        
        int Shader::SetInt(const std::string &name, int value) {
            int id = PropertyToID(name);
            glUniform1i(id, value);
            return id;
        }
        
        void Shader::SetInt(int id, int value){
            glUniform1i(id, value);
        }
        
        int Shader::SetIntArray(const std::string& name, int* values, uint32 count)
        {
            int id = PropertyToID(name);
            glUniform1iv(id, count, values);
            return id;
        }
        
        void Shader::SetIntArray(int id, int* values, uint32 count){
            glUniform1iv(id, count, values);
        }
        
        
        int Shader::SetFloat(const std::string &name, float value) {
            int id = PropertyToID(name);
            glUniform1f(id, value);
            return id;
        }
        
        void Shader::SetFloat(int id, float value){
            glUniform1f(id, value);
        }
        
        int Shader::SetFloatArray(const std::string& name, float* values, uint32 count)
        {
            int id = PropertyToID(name);
            glUniform1fv(id, count, values);
            return id;
        }
        
        void Shader::SetFloatArray(int id, float* values, uint32 count){
            glUniform1fv(id, count, values);
        }
        
        int Shader::SetVector2(const std::string &name, const Math::Vector2 &value) {
            int id = PropertyToID(name);
            glUniform2f(id, value.x, value.y);
            return id;
        }
        
        int Shader::SetVector2(const std::string &name, float x, float y) {
            int id = PropertyToID(name);
            glUniform2f(id, x, y);
            return id;
        }
        
        void Shader::SetVector2(int id, const Math::Vector2& value){
            glUniform2f(id, value.x, value.y);
        }
        
        void Shader::SetVector2(int id, float x, float y){
            glUniform2f(id, x, y);
        }
        
        int Shader::SetVector3(const std::string &name, const Math::Vector3 &value) {
            int id = PropertyToID(name);
            glUniform3f(id, value.x, value.y, value.z);
            return id;
        }
        
        int Shader::SetVector3(const std::string &name, float x, float y, float z) {
            int id = PropertyToID(name);
            glUniform3f(id, x, y, z);
            return id;
        }
        
        void Shader::SetVector3(int id, const Math::Vector3& value){
            glUniform3f(id, value.x, value.y, value.z);
        }
        
        void Shader::SetVector3(int id, float x, float y, float z){
            glUniform3f(id, x, y, z);
        }
        
        int Shader::SetVector4(const std::string &name, const Math::Vector4 &value) {
            int id = PropertyToID(name);
            glUniform4f(id, value.x, value.y, value.z, value.w);
            return id;
        }
        
        int Shader::SetVector4(const std::string &name, float x, float y, float z, float w) {
            int id = PropertyToID(name);
            glUniform4f(id, x, y, z, w);
            return id;
        }
        
        void Shader::SetVector4(int id, const Math::Vector4& value){
            glUniform4f(id, value.x, value.y, value.z, value.w);
        }
        
        void Shader::SetVector4(int id, float x, float y, float z, float w){
            glUniform4f(id, x, y, z, w);
        }
        
        int Shader::SetMatrix4(const std::string &name, const Math::Matrix4 &value) {
            int id = PropertyToID(name);
            glUniformMatrix4fv(id, 1, GL_FALSE, value.ValuePtr());
            return id;
        }
        
        void Shader::SetMatrix4(int id, const Math::Matrix4& value){
            glUniformMatrix4fv(id, 1, GL_FALSE, value.ValuePtr());
        }
        
        int Shader::SetColor(const std::string& name, const Color& value){
            int id = PropertyToID(name);
            glUniform4f(id, value.x, value.y, value.z, value.w);
            return id;
        }
        
        void Shader::SetMaterial(const std::string& name, const Material& value)
        {
            SetFloat(name + ".metallic", value.metallic);
            SetFloat(name + ".specular", value.specular);
            SetFloat(name + ".roughness", value.roughness);
        }
        void Shader::SetLight(const std::string& name, const Light& value)
        {
            SetVector3(name + ".position", value.position);
            SetVector3(name + ".color", value.color);
            SetFloat(name + ".ambientStrength", value.ambientStrength);
        }
        
        int Shader::PropertyToID(const std::string &name) {
            if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
                return uniformLocationCache[name];
            }
            
            GLint location = glGetUniformLocation(rendererID, name.c_str());
            if (location == -1) {
                std::cout << "Warning: Shader Property " << name << " does not exist" << std::endl;
            }
            uniformLocationCache[name] = location;
            return location;
        }
        
        SharedPtr<Shader> Shader::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        {
            return CreateSharedPtr<Shader>(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        }
    
}

