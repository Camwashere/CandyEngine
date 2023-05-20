#include "VertexArray.hpp"
#include "VertexArray.hpp"
#include "../GraphicsContext.hpp"
#include "../Renderer.hpp"

namespace Candy::Graphics {
        
        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
        {
            switch (type)
            {
                case ShaderDataType::Float:    return GL_FLOAT;
                case ShaderDataType::Float2:   return GL_FLOAT;
                case ShaderDataType::Float3:   return GL_FLOAT;
                case ShaderDataType::Float4:   return GL_FLOAT;
                case ShaderDataType::Mat3:     return GL_FLOAT;
                case ShaderDataType::Mat4:     return GL_FLOAT;
                case ShaderDataType::Int:      return GL_INT;
                case ShaderDataType::Int2:     return GL_INT;
                case ShaderDataType::Int3:     return GL_INT;
                case ShaderDataType::Int4:     return GL_INT;
                case ShaderDataType::Bool:     return GL_BOOL;
                default:
                    std::cerr << "Unknown shader data type" << std::endl;
                    return 0;
            }
        }
        VertexArray::VertexArray() {
            glCreateVertexArrays(1, &rendererID);
            //GLCall(glGenVertexArrays(1, &rendererID));
        }
        
        VertexArray::~VertexArray() {
            glDeleteVertexArrays(1, &rendererID);
        }
        
        void VertexArray::Bind() const {
            glBindVertexArray(rendererID);
        }
        
        void VertexArray::Unbind() const {
            glBindVertexArray(0);
        }
        
        void VertexArray::AddVertexBuffer(const SharedPtr<VertexBuffer> &vertexBuffer) {
            Bind();
            vertexBuffer->Bind();
            const auto &layout = vertexBuffer->GetLayout();
            for (const auto& element : layout)
            {
                switch (element.type)
                {
                    case ShaderDataType::Float:
                    case ShaderDataType::Float2:
                    case ShaderDataType::Float3:
                    case ShaderDataType::Float4:
                    {
                        glEnableVertexAttribArray(vertexBufferIndex);
                        glVertexAttribPointer(vertexBufferIndex,
                                              element.GetComponentCount(),
                                              ShaderDataTypeToOpenGLBaseType(element.type),
                                              element.normalized ? GL_TRUE : GL_FALSE,
                                              layout.GetStride(),
                                              (const void*)element.offset);
                        vertexBufferIndex++;
                        break;
                    }
                    case ShaderDataType::Int:
                    case ShaderDataType::Int2:
                    case ShaderDataType::Int3:
                    case ShaderDataType::Int4:
                    case ShaderDataType::Bool:
                    {
                        glEnableVertexAttribArray(vertexBufferIndex);
                        glVertexAttribIPointer(vertexBufferIndex,
                                               element.GetComponentCount(),
                                               ShaderDataTypeToOpenGLBaseType(element.type),
                                               layout.GetStride(),
                                               (const void*)element.offset);
                        vertexBufferIndex++;
                        break;
                    }
                    case ShaderDataType::Mat3:
                    case ShaderDataType::Mat4:
                    {
                        uint8_t count = element.GetComponentCount();
                        for (uint8_t i = 0; i < count; i++)
                        {
                            glEnableVertexAttribArray(vertexBufferIndex);
                            glVertexAttribPointer(vertexBufferIndex,
                                                  count,
                                                  ShaderDataTypeToOpenGLBaseType(element.type),
                                                  element.normalized ? GL_TRUE : GL_FALSE,
                                                  layout.GetStride(),
                                                  (const void*)(element.offset + sizeof(float) * count * i));
                            glVertexAttribDivisor(vertexBufferIndex, 1);
                            vertexBufferIndex++;
                        }
                        break;
                    }
                    
                    default:
                        std::cerr << "Unkown shader data type" << std::endl;
                }
            }
            
            vertexBuffers.push_back(vertexBuffer);
        }
        
        void VertexArray::SetIndexBuffer(const SharedPtr<IndexBuffer> &indexBufferValue)
        {
            Bind();
            indexBufferValue->Bind();
            indexBuffer = indexBufferValue;
            
        }
        
        SharedPtr<VertexArray> VertexArray::Create()
        {
            switch(Renderer::GetAPI())
            {
                case RendererAPI::API::None: return nullptr;
                case RendererAPI::API::OpenGL: return CreateSharedPtr<VertexArray>();
                default:
                    std::cerr << "Unknown renderer api" << std::endl;
                    return nullptr;
            }
        }
}

