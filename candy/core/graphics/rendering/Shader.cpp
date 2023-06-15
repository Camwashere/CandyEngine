#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include "glad/glad.h"
#include "../../../include/Candy/Graphics.hpp"


namespace Candy::Graphics{
    
    namespace Utils{
        static GLenum ShaderTypeFromString(const std::string& type)
        {
            if (type == "vertex")
                return GL_VERTEX_SHADER;
            if (type == "fragment" || type == "pixel")
                return GL_FRAGMENT_SHADER;
            
            CANDY_CORE_ASSERT(false, "Unknown shader type!");
            return 0;
        }
        
        
        static const char* GLShaderStageToString(GLenum stage)
        {
            switch (stage)
            {
                case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
                case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
            }
            CANDY_CORE_ASSERT(false);
            return nullptr;
        }
        
        static const char* GetCacheDirectory()
        {
            // TODO: make sure the assets directory is valid
            return "assets/cache/shader";
        }
        
        static void CreateCacheDirectoryIfNeeded()
        {
            std::string cacheDirectory = GetCacheDirectory();
            if (!std::filesystem::exists(cacheDirectory))
                std::filesystem::create_directories(cacheDirectory);
        }
        
        static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
        {
            switch (stage)
            {
                case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
                case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
            }
            CANDY_CORE_ASSERT(false);
            return "";
        }
        
        static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
        {
            switch (stage)
            {
                case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
                case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
            }
            CANDY_CORE_ASSERT(false);
            return "";
        }
    }
        
        
        Shader::Shader() {}
    
        Shader::Shader(std::string  shaderFilePath) : filepath(std::move(shaderFilePath))
        {
            Utils::CreateCacheDirectoryIfNeeded();
            std::string source = ReadFile(filepath);
            auto shaderSources = PreProcess(source);
            
            
            CompileShaders(shaderSources[GL_VERTEX_SHADER].c_str(), shaderSources[GL_FRAGMENT_SHADER].c_str());
            
            // Extract name from filepath
            auto lastSlash = filepath.find_last_of("/\\");
            lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
            auto lastDot = filepath.rfind('.');
            auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
            name = filepath.substr(lastSlash, count);
        
        }
    
        Shader::Shader(std::string  shaderName, const std::string& vertexPath, const std::string& fragmentPath)
        : name(std::move(shaderName))
        {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode = ReadFile(vertexPath);
            std::string fragmentCode = ReadFile(fragmentPath);
           
            CompileShaders(vertexCode.c_str(), fragmentCode.c_str());
        }
        Shader::~Shader()
        {
            glDeleteProgram(rendererID);
        }
    
    std::string Shader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else
            {
                CANDY_CORE_ERROR("Could not read from file '{0}'", filepath);
            }
        }
        else
        {
            CANDY_CORE_ERROR("Could not open file '{0}'", filepath);
        }
        
        return result;
    
    }
    std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;
        
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            CANDY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            CANDY_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");
            
            size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            CANDY_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line
            
            shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }
        
        return shaderSources;
    
    }
    
    bool Shader::CheckCompileErrors(GLuint shader, const std::string& type)
    {
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
    void Shader::CompileShaders(const char *vertexShaderCode, const char *fragmentShaderCode)
    {
        uint32 vertex, fragment;
        
        
        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, NULL);
        glCompileShader(vertex);
        if (!CheckCompileErrors(vertex, "VERTEX"))
        {
            std::cerr << "Failed to compile vertex shader!" << std::endl;
            
        }
        // print compile errors if any
        
        
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragment);
        if (!CheckCompileErrors(fragment, "FRAGMENT"))
        {
            std::cerr << "Failed to compile fragment shader!" << std::endl;
            
        }
        
        // print compile errors if any
        
        
        // shader Program
        CreateProgram(vertex, fragment);
        
    }
    void Shader::CreateProgram(uint32 vertex, uint32 fragment)
    {
        // shader Program
        rendererID = glCreateProgram();
        glAttachShader(rendererID, vertex);
        glAttachShader(rendererID, fragment);
        glLinkProgram(rendererID);
        if (!CheckCompileErrors(rendererID, "PROGRAM"))
        {
            CANDY_CORE_ERROR("Failed to compile shader program {}", name);
            return;
        }
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
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
        SharedPtr<Shader> Shader::Create(const std::string& filepath)
        {
            return CreateSharedPtr<Shader>(filepath.c_str());
        }
        SharedPtr<Shader> Shader::Create(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        {
            return CreateSharedPtr<Shader>(shaderName, vertexShaderPath.c_str(), fragmentShaderPath.c_str());
        }
    
}

