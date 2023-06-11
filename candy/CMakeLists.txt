cmake_minimum_required(VERSION 3.25)
project(Candy)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --enable-llvm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")



set(SOURCE_BASE_FILES core/base/general/CandyAssert.hpp core/base/general/CandyConcepts.hpp core/base/general/CandyCoreBase.hpp core/base/primitive/CandyString.hpp core/base/primitive/CandyString.cpp
        core/base/primitive/PrimitiveTypes.hpp core/base/primitive/UUID.hpp core/base/primitive/UUID.cpp core/base/primitive/RawBuffer.hpp core/base/debug/Logger.hpp core/base/primitive/KeyCodes.hpp
        core/base/debug/Log.hpp core/base/debug/Log.cpp core/base/debug/Profiler.hpp core/base/primitive/MouseCodes.hpp core/base/general/PlatformDetection.hpp)

set(SOURCE_UTIL_FILES core/utils/Stopwatch.hpp core/utils/Stopwatch.cpp core/utils/FileSystem.hpp core/utils/FileSystem.cpp core/utils/IDManager.hpp core/utils/FileDialogs.hpp core/utils/UtilsAll.hpp core/utils/FileDialogs.cpp)

set(SOURCE_MATH_FILES core/math/general/MathOps.hpp core/math/linalg/LinalgForwardDef.hpp core/math/linalg/vector/base/VectorBase.hpp core/math/linalg/vector/base/VectorExpression.hpp core/math/linalg/vector/Vector2.hpp core/math/linalg/vector/Vector2.cpp core/math/linalg/vector/VectorAll.hpp core/math/linalg/LinalgAll.hpp core/math/linalg/vector/Vector3.hpp core/math/linalg/vector/Vector4.hpp core/math/linalg/vector/Vector3.cpp core/math/linalg/vector/Vector4.cpp core/math/linalg/vector/Vector2Int.hpp core/math/linalg/vector/Vector3Int.hpp core/math/linalg/vector/Vector2Int.cpp core/math/linalg/vector/Vector3Int.cpp core/math/linalg/quaternion/Quaternion.hpp core/math/linalg/quaternion/Quaternion.cpp core/math/linalg/matrix/Matrix4.hpp core/math/linalg/matrix/Matrix4.cpp core/math/general/Random.hpp core/math/general/Random.cpp core/math/general/Range.hpp core/math/general/Limit.hpp core/math/linalg/matrix/base/Matrix.hpp core/math/linalg/matrix/MatrixAll.hpp core/math/general/MathGeneralAll.hpp core/math/direction/Direction2.hpp core/math/direction/Direction2.cpp core/math/direction/Direction3.hpp core/math/direction/Direction3.cpp core/math/geometry/2d/Rectangle.hpp core/math/geometry/2d/Rectangle.cpp core/math/geometry/GeometryAll.hpp)

set(SOURCE_COLLECTIONS_FILES core/collections/MultiArray.hpp core/collections/HeapArray3D.hpp core/collections/Array2D.hpp core/collections/Array3D.hpp)

set(SOURCE_NOISE_FILES core/noise/PerlinNoise.hpp core/noise/PerlinNoise.cpp)

set(SOURCE_APPLICATION_FILES core/application/Project.hpp core/application/ProjectSerializer.hpp core/application/ProjectSerializer.cpp core/application/Project.cpp core/application/Application.hpp core/application/Window.hpp core/application/Application.cpp core/application/Window.cpp)

set(SOURCE_GRAPHICS_FILES core/graphics/color/Color.hpp core/graphics/color/Color32.cpp core/graphics/color/Color32.hpp core/graphics/color/ColorBase.cpp core/graphics/color/ColorBase.hpp core/graphics/color/ColorHSL.hpp core/graphics/color/ColorHSV.hpp core/graphics/color/ColorForwardDef.hpp core/graphics/color/ColorAll.hpp core/graphics/color/ColorHSL.cpp core/graphics/color/ColorHSV.cpp core/graphics/color/Color.cpp core/graphics/layers/Layer.hpp core/graphics/layers/Layer.cpp core/graphics/layers/LayerStack.hpp core/graphics/layers/LayerStack.cpp core/graphics/layers/UILayer.hpp core/graphics/layers/UILayer.cpp core/graphics/layers/LayersAll.hpp core/graphics/model/Mesh.hpp core/graphics/model/Mesh.cpp core/graphics/rendering/Shader.hpp core/graphics/rendering/Shader.cpp core/graphics/rendering/RendererAPI.hpp core/graphics/rendering/RendererAPI.cpp core/graphics/rendering/Renderer.hpp core/graphics/rendering/Renderer.cpp core/graphics/rendering/RenderCommand.hpp core/graphics/rendering/RenderCommand.cpp core/graphics/rendering/Material.hpp core/graphics/rendering/GraphicsContext.hpp core/graphics/rendering/GraphicsContext.cpp core/graphics/rendering/camera/Camera.hpp core/graphics/rendering/camera/Camera.cpp core/graphics/rendering/data/VertexBuffer.cpp core/graphics/rendering/data/VertexBuffer.hpp core/graphics/rendering/data/VertexArray.cpp core/graphics/rendering/data/VertexArray.hpp core/graphics/rendering/data/UniformBuffer.cpp core/graphics/rendering/data/UniformBuffer.hpp core/graphics/rendering/data/IndexBuffer.cpp core/graphics/rendering/data/IndexBuffer.hpp core/graphics/rendering/data/FrameBuffer.cpp core/graphics/rendering/data/FrameBuffer.hpp core/graphics/rendering/data/RenderingMode.hpp core/graphics/rendering/data/BufferLayout.hpp core/graphics/rendering/data/RenderingDataAll.hpp core/graphics/rendering/data/texture/Texture.cpp core/graphics/rendering/data/texture/Texture.hpp core/graphics/rendering/data/texture/PixelManager.cpp core/graphics/rendering/data/texture/PixelManager.hpp core/graphics/rendering/data/texture/TextureAll.hpp core/graphics/rendering/RenderingAll.hpp core/graphics/rendering/camera/EditorCamera.hpp core/graphics/rendering/camera/EditorCamera.cpp core/graphics/rendering/camera/CameraAll.hpp core/graphics/rendering/Renderer2D.hpp core/graphics/rendering/camera/OrthographicCamera.hpp core/graphics/rendering/camera/OrthographicCamera.cpp core/graphics/rendering/Renderer2D.cpp core/graphics/rendering/camera/OrthographicCameraController.hpp core/graphics/rendering/camera/OrthographicCameraController.cpp)

set(SOURCE_EVENT_FILES core/event/events/Event.hpp core/event/events/EventDispatcher.hpp core/event/events/IEventLIstener.hpp core/event/events/KeyEvent.hpp core/event/events/MouseEvent.hpp core/event/events/WindowEvent.hpp core/event/events/KeyEvent.cpp core/event/events/MouseEvent.cpp core/event/events/WindowEvent.cpp core/event/input/Input.hpp core/event/input/Input.cpp)

set(SOURCE_ECS_FILES core/ecs/entity/Entity.hpp core/ecs/component/BaseComponents.hpp core/ecs/internal/EntityManager.hpp core/ecs/internal/ComponentManager.hpp core/ecs/internal/InternalBase.hpp
        core/ecs/internal/Registry.hpp core/ecs/internal/System.hpp core/ecs/internal/SystemManager.hpp core/ecs/scene/Scene.hpp core/ecs/scene/Scene.cpp core/ecs/scene/SceneCamera.hpp core/ecs/scene/SceneCamera.cpp core/ecs/scene/SceneSerializer.hpp core/ecs/scene/SceneSerializer.cpp core/ecs/entity/ScriptableEntity.hpp)

set(SOURCE_SCRIPTING_FILES core/scripting/ScriptEngine.hpp core/scripting/ScriptEngine.cpp core/scripting/ScriptGlue.hpp core/scripting/ScriptGlue.cpp)

set(SOURCE_UI_FILES ui/core/base/UINode.hpp ui/core/widget/base/WidgetBase.hpp ui/core/widget/button/Button.hpp ui/core/widget/button/ButtonAll.hpp ui/core/widget/color/ColorEdit3.hpp ui/core/widget/color/ColorEdit4.hpp ui/core/widget/color/ColorPicker.hpp ui/core/widget/color/ColorWidgetAll.hpp ui/core/widget/drag/DragBase.hpp ui/core/widget/drag/DragBaseN.hpp ui/core/widget/drag/DragDouble.hpp ui/core/widget/drag/DragFloat.hpp ui/core/widget/drag/DragInt.hpp ui/core/widget/drag/DragVector2.hpp ui/core/widget/drag/DragVector3.hpp ui/core/widget/drag/DragVector4.hpp ui/core/widget/drag/DragWidgetAll.hpp ui/core/widget/misc/Spacer.hpp ui/core/widget/WidgetAll.hpp ui/editor/EditorPane.hpp ui/editor/EditorPane.cpp ui/editor/EditorLayout.cpp ui/editor/EditorAll.hpp ui/core/base/ScopedStyleColor.hpp)

set(SOURCE_VOXEL_FILES voxel/block/Block.hpp voxel/block/Block.cpp voxel/block/BlockAll.hpp voxel/block/BlockType.hpp voxel/block/BlockType.cpp voxel/block/BlockTypeManager.hpp
        voxel/block/BlockTypeManager.cpp voxel/block/VoxelData.hpp voxel/block/VoxelData.cpp voxel/chunk/Chunk.hpp voxel/chunk/Chunk.cpp voxel/chunk/ChunkAll.hpp
        voxel/chunk/ChunkManager.hpp voxel/chunk/ChunkManager.cpp voxel/structure/VoxelOctree.hpp voxel/structure/VoxelOctree.cpp voxel/structure/VoxelOctree.cpp)

set(SOURCE_AUDIO_FILES core/audio/AudioManager.hpp core/audio/AudioManager.cpp core/audio/mixing/Mixer.hpp core/audio/mixing/Mixer.cpp core/audio/mixing/plugins/MixingPlugin.hpp core/audio/mixing/plugins/VolumePlugin.hpp core/audio/mixing/plugins/VolumePlugin.cpp core/audio/mixing/plugins/PluginsAll.hpp)

set(CANDY_INCLUDE_FILES include/Candy/Collections.hpp include/Candy/App.hpp include/Candy/Noise.hpp include/Candy/Utils.hpp include/Candy/ECS.hpp
        include/Candy/Graphics.hpp include/Candy/Math.hpp include/Candy/Events.hpp include/Candy/CandyEngineCore.hpp include/Candy/CandyEngineBase.hpp
        include/Candy/UI.hpp include/Candy/CandyEngine.hpp include/Candy/Voxel.hpp include/Candy/Scripting.hpp)


set(SOURCE_FILES ${SOURCE_BASE_FILES} ${SOURCE_UTIL_FILES} ${SOURCE_COLLECTIONS_FILES} ${SOURCE_MATH_FILES} ${SOURCE_NOISE_FILES}
        ${SOURCE_APPLICATION_FILES} ${SOURCE_GRAPHICS_FILES} ${SOURCE_EVENT_FILES} ${SOURCE_ECS_FILES} ${SOURCE_SCRIPTING_FILES} ${SOURCE_UI_FILES} ${SOURCE_VOXEL_FILES} ${SOURCE_AUDIO_FILES} ${CANDY_INCLUDE_FILES} include/Candy/EntryPoint.hpp)

set(LIB_FILES lib/stb/stb_image.h lib/stb/stb_image.cpp lib/imgui/imstb_truetype.h lib/imgui/imstb_textedit.h lib/imgui/imstb_rectpack.h lib/imgui/imgui_widgets.cpp lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp
        lib/imgui/imgui_draw.cpp lib/imgui/imgui_impl_glfw.cpp lib/imgui/imgui_impl_glfw.h lib/imgui/imgui_impl_opengl3.cpp lib/imgui/imgui_impl_opengl3.h lib/imgui/imgui_tables.cpp
        lib/filewatch/FileWatch.hpp)




set(ALL_FILES ${SOURCE_FILES} ${LIB_FILES})





find_package(fmt CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)



add_subdirectory(lib/glad)
add_subdirectory(lib/entt)

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})


target_include_directories(${PROJECT_NAME} PUBLIC lib/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC lib/stb)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/filewatch)
target_include_directories(${PROJECT_NAME} PUBLIC lib/entt/src)
target_include_directories(${PROJECT_NAME} PUBLIC include)



if (NOT DEFINED MONO_HOME)
    set(MONO_HOME "C:/Program Files/Mono")
endif()


target_include_directories(${PROJECT_NAME} PRIVATE "${MONO_HOME}/include/mono-2.0")



target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only glfw glad SndFile::sndfile portaudio "${MONO_HOME}/bin/mono-2.0-sgen.dll")

configure_file("${MONO_HOME}/bin/mono-2.0-sgen.dll" "${PROJECT_BINARY_DIR}/mono-2.0-sgen.dll" COPYONLY)
