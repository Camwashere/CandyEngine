#pragma once

#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H
#include <Candy/CandyEngineBase.hpp>
#include <vector>
namespace Candy::Graphics{
    
    enum class FrameBufferTextureFormat
    {
        None = 0,
        
        // Color
        RGBA8,
        RED_INTEGER,
        
        // Depth/stencil
        DEPTH24STENCIL8,
        
        // Defaults
        Depth = DEPTH24STENCIL8
    };
    
    struct FrameBufferTextureSpecification
    {
        FrameBufferTextureSpecification() = default;
        FrameBufferTextureSpecification(FrameBufferTextureFormat format)
                : textureFormat(format) {}
        
        FrameBufferTextureFormat textureFormat = FrameBufferTextureFormat::None;
        // TODO: filtering/wrap
    };
    
    struct FrameBufferAttachmentSpecification
    {
        FrameBufferAttachmentSpecification() = default;
        FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
                : attachments(attachments) {}
        
        std::vector<FrameBufferTextureSpecification> attachments;
    };
    
    struct FrameBufferSpecification
    {
        uint32 width = 0, height = 0;
        FrameBufferAttachmentSpecification attachments;
        uint32 samples = 1;
        
        bool swapChainTarget = false;
    };
    class FrameBuffer
    {
    private:
        uint32 rendererID = 0;
        FrameBufferSpecification specification;
        
        std::vector<FrameBufferTextureSpecification> colorAttachmentSpecifications;
        FrameBufferTextureSpecification depthAttachmentSpecification = FrameBufferTextureFormat::None;
        std::vector<uint32> colorAttachments;
        uint32 depthAttachment = 0;
    public:
        FrameBuffer(const FrameBufferSpecification& spec);
        ~FrameBuffer();
        
        void Invalidate();
        
        void Bind();
        void Unbind();
        
        void Resize(uint32 width, uint32 height);
        int ReadPixel(uint32 attachmentIndex, int x, int y);
        
        void ClearAttachment(uint32 attachmentIndex, int value);
        
        uint32 GetColorAttachmentRendererID(uint32 index = 0) const  { return colorAttachments[index]; }
        
        const FrameBufferSpecification& GetSpecification() const  { return specification; }
        
    };
}
#endif //ENGINE_FRAMEBUFFER_H

