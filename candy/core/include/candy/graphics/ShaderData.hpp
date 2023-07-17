#pragma once
#include <array>
#include <vulkan/vulkan.h>
namespace Candy::Graphics
{
    enum class ShaderDataType : uint8_t
    {
        Float = 0,
        Float2=1,
        Vector2=1,
        Float3=2,
        Vector3=2,
        Float4=3,
        Vector4=3,
        
        Int=4,
        Int2=5,
        Vector2Int=5,
        Int3=6,
        Vector3Int=6,
        Int4=7,
        Vector4Int=7,
        
        UInt=8,
        UInt2=9,
        Vector2Uint=9,
        UInt3=10,
        Vector3Uint=10,
        UInt4=11,
        Vector4Uint=11,
        
        
        NONE,
        
    };
    
    class ShaderData
    {
    private:
        static constexpr size_t ARRAY_SIZE=12;
        static inline std::array<VkFormat, ARRAY_SIZE> vulkanFormatArray{
            VK_FORMAT_R32_SFLOAT, //Float
            VK_FORMAT_R32G32_SFLOAT, //Float2
            VK_FORMAT_R32G32B32_SFLOAT, //Float3
            VK_FORMAT_R32G32B32A32_SFLOAT, //Float4
            
            VK_FORMAT_R32_SINT, //Int
            VK_FORMAT_R32G32_SINT, //Int2
            VK_FORMAT_R32G32B32_SINT, //Int3
            VK_FORMAT_R32G32B32A32_SINT, //Int4
            
            VK_FORMAT_R32_UINT, //UInt
            VK_FORMAT_R32G32_UINT, //UInt2
            VK_FORMAT_R32G32B32_UINT, //UInt3
            VK_FORMAT_R32G32B32A32_UINT, //UInt4
        };
        
        static inline std::array<size_t, ARRAY_SIZE> componentCountArray{
            // Floats
            1, 2, 3, 4,
            
            // Ints
            1, 2, 3, 4,
            
            // UInts
            1, 2, 3, 4,
            
        };
        
        static inline std::array<size_t, ARRAY_SIZE> sizeTypeArray{
            4,
            4*2,
            4*3,
            4*4,
            
            4,
            4*2,
            4*3,
            4*4,
            
            4,
            4*2,
            4*3,
            4*4,
        };
        
    public:
        static VkFormat ShaderDataTypeToVulkanFormat(ShaderDataType type);
        static size_t ShaderDataTypeSize(ShaderDataType type);
        static size_t ShaderDataTypeComponentCount(ShaderDataType type);
        
        
    };
    
    
}
