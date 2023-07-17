#include <candy/graphics/ShaderData.hpp>
#include <CandyPch.hpp>
namespace Candy::Graphics
{
    VkFormat ShaderData::ShaderDataTypeToVulkanFormat(ShaderDataType type)
    {
        CANDY_CORE_ASSERT(((uint8_t)type) < vulkanFormatArray.size(), "Unknown ShaderDataType!");
        return vulkanFormatArray[(uint8_t)type];
    }
    size_t ShaderData::ShaderDataTypeSize(ShaderDataType type)
    {
        CANDY_CORE_ASSERT(((uint8_t)type) < sizeTypeArray.size(), "Unknown ShaderDataType!");
        return sizeTypeArray[(uint8_t)type];
    }
    
    size_t ShaderData::ShaderDataTypeComponentCount(ShaderDataType type)
    {
        CANDY_CORE_ASSERT((uint8_t)type < componentCountArray.size(), "Unknown ShaderDataType!");
        return componentCountArray[(uint8_t)type];
    }
}