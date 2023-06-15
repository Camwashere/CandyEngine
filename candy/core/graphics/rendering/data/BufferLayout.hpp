#pragma once

#include <Candy/Math.hpp>

namespace Candy::Graphics {
        enum class ShaderDataType
        {
            None = 0,
            Float,
            Float2,
            Float3,
            Float4,
            Mat3,
            Mat4,
            Int,
            Int2,
            Int3,
            Int4,
            Bool,
        };
        static uint32 ShaderDataTypeSize(ShaderDataType type)
        {
            switch(type)
            {
                case ShaderDataType::Float:    return 4;
                case ShaderDataType::Float2:   return 4 * 2;
                case ShaderDataType::Float3:   return 4 * 3;
                case ShaderDataType::Float4:   return 4 * 4;
                case ShaderDataType::Mat3:     return 4 * 3 * 3;
                case ShaderDataType::Mat4:     return 4 * 4 * 4;
                case ShaderDataType::Int:      return 4;
                case ShaderDataType::Int2:     return 4 * 2;
                case ShaderDataType::Int3:     return 4 * 3;
                case ShaderDataType::Int4:     return 4 * 4;
                case ShaderDataType::Bool:     return 1;
                default:
                    std::cerr << "Unknown shader data type!" << std::endl;
                    return 0;
            }
        }
        struct BufferElement {
        public:
            ShaderDataType type;
            std::string name;
            
            uint32 size;
            std::size_t offset;
            bool normalized;
            
            BufferElement()=default;
            
            BufferElement(ShaderDataType elementType, const std::string& elementName, bool normalized=false) : type(elementType), name(elementName), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
            {
            
            }
            
            uint32 GetComponentCount()const
            {
                switch (type)
                {
                    case ShaderDataType::Float:   return 1;
                    case ShaderDataType::Float2:  return 2;
                    case ShaderDataType::Float3:  return 3;
                    case ShaderDataType::Float4:  return 4;
                    case ShaderDataType::Mat3:    return 3; // 3* float3
                    case ShaderDataType::Mat4:    return 4; // 4* float4
                    case ShaderDataType::Int:     return 1;
                    case ShaderDataType::Int2:    return 2;
                    case ShaderDataType::Int3:    return 3;
                    case ShaderDataType::Int4:    return 4;
                    case ShaderDataType::Bool:    return 1;
                    default:
                        std::cerr << "Unknown shader data type in Get Component Count" << std::endl;
                }
                return 0;
            }
            
            
            
            inline uint32 GetTypeSize() const { return ShaderDataTypeSize(type); }
            
        };
        
        class BufferLayout {
        private:
            std::vector<BufferElement> elements;
            uint stride=0;
            std::size_t offset=0;
        
        private:
            void CalculateOffsetsAndStride()
            {
                offset=0;
                stride=0;
                for (auto& element : elements)
                {
                    element.offset = offset;
                    offset += element.size;
                    stride += element.size;
                }
            }
        
        public:
            BufferLayout() : stride(0), offset(0) {}
            BufferLayout(std::initializer_list<BufferElement> bufferElements) : elements(bufferElements)
            {
                CalculateOffsetsAndStride();
            }
            
            
            template<typename T>
            void Push(const std::string& name) {
                //std::cout << "GAY" << std::endl;
                static_assert(Candy::always_false<T>);
            }
            
            
            inline const std::vector<BufferElement>& GetElements() const { return elements; }
            std::vector<BufferElement>::iterator begin() { return elements.begin(); }
            std::vector<BufferElement>::iterator end() { return elements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
            
            inline uint GetStride() const { return stride; }
            inline std::size_t GetOffset()const{return offset;}
            
        };
        
        template<>
        inline void BufferLayout::Push<float>(const std::string& name) {
            BufferElement element(ShaderDataType::Float, name, false);
            element.offset=offset;
            offset+=element.size;
            stride+=element.size;
            elements.push_back(element);
            
        }
        template<>
        inline void BufferLayout::Push<uint32>(const std::string& name) {
            BufferElement element(ShaderDataType::Int, name, false);
            element.offset=offset;
            offset+=element.size;
            stride+=element.size;
            elements.push_back(element);
        }
        
        template<>
        inline void BufferLayout::Push<Math::Vector2>(const std::string& name) {
            BufferElement element(ShaderDataType::Float2, name, false);
            element.offset=offset;
            offset+=element.size;
            stride+=element.size;
            elements.push_back(element);
            
        }
        template<>
        inline void BufferLayout::Push<Math::Vector3>(const std::string& name) {
            BufferElement element(ShaderDataType::Float3, name, false);
            element.offset=offset;
            offset+=element.size;
            stride+=element.size;
            elements.push_back(element);
            
        }
        template<>
        inline void BufferLayout::Push<Math::Vector4>(const std::string& name) {
            BufferElement element(ShaderDataType::Float4, name, false);
            element.offset=offset;
            offset+=element.size;
            stride+=element.size;
            elements.push_back(element);
            
        }
}

