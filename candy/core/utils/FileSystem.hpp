#pragma once

#include "../base/primitive/RawBuffer.hpp"
#include <filesystem>
namespace Candy::Utils{
    class FileSystem
    {
    public:
        static Buffer ReadFileBinary(const std::filesystem::path& filepath);
    };
}