#include <candy/graphics/PixelBuffer.hpp>
#include <candy/graphics/Vulkan.hpp>
#include <candy/graphics/RenderCommand.hpp>
namespace Candy::Graphics
{
  PixelBuffer::PixelBuffer(const Math::Vector2u& sizeOfImage)
  : VulkanBuffer(sizeof(int), BufferType::PIXEL)
  {
    imageSize = sizeOfImage;
    //CANDY_CORE_INFO("IMAGE SIZE: {}", imageSize);
    pixels = new int[1];
    VulkanBuffer::CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buffer, &allocation);
    Vulkan::DeletionQueue().Push(this);
  }
  
  PixelBuffer::~PixelBuffer()
  {
    delete[] pixels;
  }
  int PixelBuffer::ReadPixel(int x, int y)
  {
    CopyImage(Renderer::GetCurrentFrame().viewportData.selectionImage, x, y);
    int pixel = pixels[0];
    vmaUnmapMemory(Vulkan::Allocator(), allocation); // Unmap memory after reading pixel value from it
    return pixel;
  }
  Math::Vector2u PixelBuffer::GetImageSize()const
  {
    return imageSize;
  }
  int PixelBuffer::GetPixel(int x, int y)
  {
    int pixelIndex = y * (int)imageSize.x + x;
    CANDY_CORE_ASSERT(pixelIndex < imageSize.x * imageSize.y, "Pixel index out of bounds");
    return pixels[pixelIndex];
  }
  
  void PixelBuffer::CopyImage(VkImage image, int x, int y)
  {
    RenderCommand::TransitionImageLayout(image, VK_FORMAT_R32_SINT, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    Renderer::GetCurrentFrame().commandBuffer.CopyImageToBuffer(image, buffer, x, y, 1, 1);
    vmaMapMemory(Vulkan::Allocator(), allocation, &data);
    memcpy(pixels, static_cast<int*>(data), sizeof(int));
  }
}