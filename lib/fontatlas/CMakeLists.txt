cmake_minimum_required(VERSION 3.26)

project(FontAtlas)

set(CMAKE_CXX_STANDARD 23)

set(TINYXML2_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lib/tinyxml2/tinyxml2.h)

set(FREETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype2/include)
set(FREETYPE_LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/lib/freetype2/libfreetyped.a)

find_package(PNG REQUIRED)
if (PNG_FOUND)
    message(STATUS "Found libpng")
else()
    message(FATAL_ERROR "Could not find libpng. Cannot build FontAtlasLib")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype2)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/tinyxml2 ${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype2/include)

set(FIELD_GEN_INCLUDE_FILES
        include/FontAtlas/Field/msdfVec2.hpp
        include/FontAtlas/Field/Arithmetics.hpp
        include/FontAtlas/Field/Bitmap.hpp
        include/FontAtlas/Field/BitmapRef.hpp
        include/FontAtlas/Field/Contour.hpp
        include/FontAtlas/Field/ContourCombiners.hpp
        include/FontAtlas/Field/EdgeColor.hpp
        include/FontAtlas/Field/EdgeColoring.hpp
        include/FontAtlas/Field/EdgeHolder.hpp
        include/FontAtlas/Field/EdgeSegments.hpp
        include/FontAtlas/Field/EdgeSelectors.hpp
        include/FontAtlas/Field/EquationSolver.hpp
        include/FontAtlas/Field/GeneratorConfig.hpp
        include/FontAtlas/Field/MSDFErrorCorrection.hpp
        include/FontAtlas/Field/PixelConversion.hpp
        include/FontAtlas/Field/Projection.hpp
        include/FontAtlas/Field/Rasterization.hpp
        include/FontAtlas/Field/Scanline.hpp
        include/FontAtlas/Field/Shape.hpp
        include/FontAtlas/Field/ShapeDescription.hpp
        include/FontAtlas/Field/ShapeDistanceFinder.hpp
        include/FontAtlas/Field/SignedDistance.hpp
        include/FontAtlas/Field/BitmapInterpolation.hpp
        include/FontAtlas/Field/msdf-error-correction.hpp
        include/FontAtlas/Field/RenderSdf.hpp
        include/FontAtlas/Field/sdf-error-estimation.hpp
        include/FontAtlas/Field/save-tiff.hpp
        include/FontAtlas/Field/save-bmp.hpp
)

set(FIELD_GEN_SOURCE_FILES src/field/Contour.cpp
        src/field/ContourCombiners.cpp
        src/field/EdgeColoring.cpp
        src/field/EdgeSegments.cpp
        src/field/EdgeSelectors.cpp
        src/field/EdgeHolder.cpp
        src/field/EquationSolver.cpp
        src/field/MSDFErrorCorrection.cpp
        src/field/Projection.cpp
        src/field/Rasterization.cpp
        src/field/Scanline.cpp
        src/field/Shape.cpp
        src/field/ShapeDescription.cpp
        src/field/SignedDistance.cpp
        src/field/msdfVec2.cpp
        src/field/msdf-error-correction.cpp
        src/field/RenderSdf.cpp
        src/field/sdf-error-estimation.cpp
        src/field/save-tiff.cpp
        src/field/save-bmp.cpp)

set(FIELD_GEN_FILES ${FIELD_GEN_INCLUDE_FILES} ${FIELD_GEN_SOURCE_FILES} include/FontAtlas/msdfgen.hpp
        src/msdfgen.cpp)

set(ATLAS_GEN_INCLUDE_FILES include/FontAtlas/Atlas/FontAtlasLoader.hpp
        include/FontAtlas/Atlas/FontData.hpp
        include/FontAtlas/Atlas/Remap.hpp
        include/FontAtlas/Atlas/AtlasGenerator.hpp
        include/FontAtlas/Atlas/AtlasStorage.hpp
        include/FontAtlas/Atlas/bitmap-blit.hpp
        include/FontAtlas/Atlas/BitmapAtlasStorage.hpp
        include/FontAtlas/Atlas/Charset.hpp
        include/FontAtlas/Atlas/csv-export.hpp
        include/FontAtlas/Atlas/DynamicAtlas.hpp
        include/FontAtlas/Atlas/FontGeometry.hpp
        include/FontAtlas/Atlas/glyph-generators.hpp
        include/FontAtlas/Atlas/GlyphBox.hpp
        include/FontAtlas/Atlas/GlyphGeometry.hpp
        include/FontAtlas/Atlas/image-encode.hpp
        include/FontAtlas/Atlas/image-save.hpp
        include/FontAtlas/Atlas/ImmediateAtlasGenerator.hpp
        include/FontAtlas/Atlas/json-export.hpp
        include/FontAtlas/Atlas/Rectangle.hpp
        include/FontAtlas/Atlas/rectangle-packing.hpp
        include/FontAtlas/Atlas/RectanglePacker.hpp
        include/FontAtlas/Atlas/shadron-preview-generator.hpp
        include/FontAtlas/Atlas/size-selectors.hpp
        include/FontAtlas/Atlas/TightAtlasPacker.hpp
        include/FontAtlas/Atlas/Workload.hpp
        include/FontAtlas/Atlas/atlas-gen-types.hpp
        include/FontAtlas/Atlas/AtlasUtfDecode.hpp)

set(ATLAS_GEN_SOURCE_FILES src/atlas/FontAtlasLoader.cpp
        src/atlas/FontData.cpp
        src/atlas/bitmap-blit.cpp
        src/atlas/Charset.cpp
        src/atlas/charset-parser.cpp
        src/atlas/csv-export.cpp
        src/atlas/FontGeometry.cpp
        src/atlas/GlyphGeometry.cpp
        src/atlas/image-encode.cpp
        src/atlas/json-export.cpp
        src/atlas/RectanglePacker.cpp
        src/atlas/shadron-preview-generator.cpp
        src/atlas/TightAtlasPacker.cpp
        src/atlas/Workload.cpp
        src/atlas/AtlasUtfDecode.cpp
        src/atlas/size-selectors.cpp
        src/atlas/glyph-generators.cpp)

set(ATLAS_GEN_FILES ${ATLAS_GEN_INCLUDE_FILES} ${ATLAS_GEN_SOURCE_FILES}
        include/FontAtlas/msdf-atlas-gen.hpp)

set(FONT_LIB_FILES ${TINYXML2_FILES})

set(FONT_FILES ${FIELD_GEN_FILES} ${ATLAS_GEN_FILES} ${FONT_LIB_FILES})

add_library(FontAtlas STATIC ${FONT_FILES})
target_link_libraries(FontAtlas PRIVATE freetype PNG::PNG)
target_include_directories(FontAtlas PUBLIC include)
target_include_directories(FontAtlas PRIVATE lib/tinyxml2 lib/freetype2/include)
target_include_directories(FontAtlas PRIVATE include/FontAtlas/Field include/FontAtlas/Atlas)
#target_include_directories(FontAtlas PUBLIC FieldGen/include FieldGen AtlasGen/include AtlasGen)

#set(TEST_FILES test/MSDFData.hpp test/Font.hpp test/Font.cpp)

#add_library(FontTestLib STATIC ${TEST_FILES})

#target_link_libraries(FontTestLib PUBLIC FontAtlas)

#add_executable(FontAtlasTest main.cpp)
#target_link_libraries(FontAtlasTest PUBLIC FontTestLib)



