#pragma once
#include <cstdint>
#include <cstring>
namespace Candy
{
    struct Buffer
    {
        uint8_t* data = nullptr;
        uint64_t size = 0;
        
        Buffer() = default;
        
        Buffer(uint64_t size)
        {
            Allocate(size);
        }
        
        Buffer(const Buffer&) = default;
        
        static Buffer Copy(Buffer other)
        {
            Buffer result(other.size);
            memcpy(result.data, other.data, other.size);
            return result;
        }
        
        void Allocate(uint64_t allocationSize)
        {
            Release();
            
            data = new uint8_t[allocationSize];
            size = allocationSize;
        }
        
        void Release()
        {
            delete[] data;
            data = nullptr;
            size = 0;
        }
        
        template<typename T>
        T* As()
        {
            return (T*)data;
        }
        
        operator bool() const
        {
            return (bool)data;
        }
    };
    
    struct ScopedBuffer
    {
    private:
        Buffer buffer;
    
    public:
        ScopedBuffer(Buffer buffer)
                : buffer(buffer)
        {
        }
        
        ScopedBuffer(uint64_t size)
                : buffer(size)
        {
        }
        
        ~ScopedBuffer()
        {
            buffer.Release();
        }
        
        uint8_t* Data() const { return buffer.data; }
        uint64_t Size() const { return buffer.size; }
        
        template<typename T>
        T* As()
        {
            return buffer.As<T>();
        }
        
        operator bool() const { return buffer; }
        
    };
}