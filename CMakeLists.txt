cmake_minimum_required(VERSION 3.26)
project(CandyEngine)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
find_package(Vulkan REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)

add_subdirectory(lib/rapidyaml)
add_subdirectory(lib/shaderc)
add_subdirectory(lib/SPIRV-Cross)
add_subdirectory(lib/antlr)
add_subdirectory(lib/fontatlas)

if(TARGET assimp::assimp)
    message(STATUS "assimp package found!")
else()
    message(STATUS "assimp package not found.")
endif()

set(INTERNAL_SOURCE_RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources/internal)
set(INTERNAL_BINARY_RESOURCES_DIR ${CMAKE_BINARY_DIR}/resources/internal)

set(TEST_PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/resources/projects/TestProject)
set(TEST_PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/projects/TestProject)

add_custom_target(
        CopyInternal ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${INTERNAL_SOURCE_RESOURCES_DIR}
        ${INTERNAL_BINARY_RESOURCES_DIR}
        COMMENT "Copying internal asset files...")

add_custom_target(
        CopyTestProject ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${TEST_PROJECT_SOURCE_DIR}
        $<$<NOT:$<STREQUAL:${TEST_PROJECT_SOURCE_DIR},${TEST_PROJECT_BINARY_DIR}>>:${TEST_PROJECT_BINARY_DIR}>
        COMMENT "Copying internal config files if they don't exist..."
)

#[[add_custom_target(
        CopyProjects ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/projects
        $<$<NOT:$<STREQUAL:${CMAKE_SOURCE_DIR}/resources/projects,${CMAKE_BINARY_DIR}/projects>>:${CMAKE_BINARY_DIR}/projects>
        COMMENT "Copying internal project files if they don't exist..."
)]]

set(CANDY_BASE_HEADERS candy/core/include/candy/base/Assert.hpp
        candy/core/include/candy/base/Base.hpp
        candy/core/include/candy/base/CandyConcepts.hpp
        candy/core/include/candy/base/Instrumentor.hpp
        candy/core/include/candy/base/KeyCodes.hpp
        candy/core/include/candy/base/Log.hpp
        candy/core/include/candy/base/MouseCodes.hpp
        candy/core/include/candy/base/PlatformDetection.hpp
        candy/core/include/candy/base/PrimitiveTypes.hpp
        candy/core/include/candy/base/RawBuffer.hpp
        candy/core/include/candy/base/UUID.hpp)

set(CANDY_BASE_SOURCES candy/core/src/base/Log.cpp
        candy/core/src/base/UUID.cpp)

set(CANDY_BASE_FILES ${CANDY_BASE_HEADERS} ${CANDY_BASE_SOURCES})

set(CANDY_COLLECTIONS_FILES candy/core/include/candy/collections/Array2D.hpp
        candy/core/include/candy/collections/Array3D.hpp
        candy/core/include/candy/collections/GenericBuffer.hpp
        candy/core/include/candy/collections/DualMap.hpp)

set(CANDY_MATH_HEADERS candy/core/include/candy/math/Vector.hpp
        candy/core/include/candy/math/Direction.hpp
        candy/core/include/candy/math/Limit.hpp
        candy/core/include/candy/math/Math.hpp
        candy/core/include/candy/math/MathOps.hpp
        candy/core/include/candy/math/Matrix.hpp
        candy/core/include/candy/math/Quaternion.hpp
        candy/core/include/candy/math/Random.hpp
        candy/core/include/candy/math/Random.inl
        candy/core/include/candy/math/Range.hpp
        candy/core/include/candy/math/Rectangle.hpp
        candy/core/include/candy/math/Transform.hpp
        candy/core/include/candy/math/vector/Vector2Base.hpp
        candy/core/include/candy/math/vector/Vector2Base.inl
        candy/core/include/candy/math/vector/Vector3Base.hpp
        candy/core/include/candy/math/vector/Vector3Base.inl
        candy/core/include/candy/math/vector/Vector4Base.hpp
        candy/core/include/candy/math/vector/Vector4Base.inl
        candy/core/include/candy/math/vector/VectorBase.hpp
        candy/core/include/candy/math/vector/VectorBaseStaticData.hpp
        candy/core/include/candy/math/vector/VectorExpression.hpp
        candy/core/include/candy/math/vector/VectorOperations.hpp
        candy/core/include/candy/math/ray/Ray3.hpp
        candy/core/include/candy/math/quaternion/QuaternionBase.hpp
        candy/core/include/candy/math/quaternion/QuaternionBase.inl
        candy/core/include/candy/math/matrix/specialization/Matrix3.hpp
        candy/core/include/candy/math/matrix/base/MatrixExpression.hpp
        candy/core/include/candy/math/direction/Direction2.hpp
        candy/core/include/candy/math/direction/Direction3.hpp
        candy/core/include/candy/math/matrix/specialization/Matrix4.hpp
        candy/core/include/candy/math/geometry/Bounds2D.hpp
        candy/core/include/candy/math/curve/BezierCurve.hpp
        candy/core/include/candy/math/curve/BezierCurveQuadratic.hpp
        candy/core/include/candy/math/curve/BezierCurveCubic.hpp
)

set(CANDY_MATH_SOURCES
        candy/core/src/math/matrix/Matrix3.cpp
        candy/core/src/math/direction/Direction2.cpp
        candy/core/src/math/direction/Direction3.cpp
        candy/core/src/math/matrix/Matrix4.cpp
        candy/core/src/math/Quaternion.cpp
        candy/core/src/math/geometry/Bounds2D.cpp
        candy/core/src/math/curve/BezierCurve.cpp
        candy/core/src/math/curve/BezierCurveQuadratic.cpp
        candy/core/src/math/curve/BezierCurveCubic.cpp)

set(CANDY_MATH_FILES ${CANDY_MATH_HEADERS} ${CANDY_MATH_SOURCES})


set(CANDY_NOISE_HEADERS candy/core/include/candy/noise/PerlinNoise.hpp)
set(CANDY_NOISE_SOURCES candy/core/src/noise/PerlinNoise.cpp)

set(CANDY_NOISE_FILES ${CANDY_NOISE_HEADERS} ${CANDY_NOISE_SOURCES})

set(CANDY_UTILS_HEADERS candy/core/include/candy/utils/FileUtils.hpp
        candy/core/include/candy/utils/FrameTime.hpp
        candy/core/include/candy/utils/IDManager.hpp
        candy/core/include/candy/utils/Stopwatch.hpp
        candy/core/include/candy/utils/Version.hpp
        candy/core/include/candy/utils/ObjectIDManager.hpp
        candy/core/include/candy/utils/ObjectIDTypes.hpp)

set(CANDY_UTILS_SOURCES candy/core/src/utils/FileUtils.cpp
        candy/core/src/utils/FrameTime.cpp
        candy/core/src/utils/Stopwatch.cpp
        candy/core/src/utils/Version.cpp)

set(CANDY_UTILS_FILES ${CANDY_UTILS_HEADERS} ${CANDY_UTILS_SOURCES})

set(CANDY_EVENT_HEADERS candy/core/include/candy/event/Event.hpp
        candy/core/include/candy/event/EventDispatcher.hpp
        candy/core/include/candy/event/Events.hpp
        candy/core/include/candy/event/IEventListener.hpp
        candy/core/include/candy/event/Input.hpp
        candy/core/include/candy/event/KeyEvent.hpp
        candy/core/include/candy/event/MouseEvent.hpp
        candy/core/include/candy/event/WindowEvent.hpp)

set(CANDY_EVENT_SOURCES candy/core/src/event/Input.cpp
        candy/core/src/event/KeyEvent.cpp
        candy/core/src/event/MouseEvent.cpp
        candy/core/src/event/WindowEvent.cpp)

set(CANDY_EVENT_FILES ${CANDY_EVENT_HEADERS} ${CANDY_EVENT_SOURCES})

set(CANDY_GRAPHICS_HEADERS candy/core/include/candy/graphics/BufferLayout.hpp
        candy/core/include/candy/graphics/Color.hpp
        candy/core/include/candy/graphics/FrameBuffer.hpp
        candy/core/include/candy/graphics/GraphicsContext.hpp
        candy/core/include/candy/graphics/IndexBuffer.hpp
        candy/core/include/candy/graphics/PixelBuffer.hpp
        candy/core/include/candy/graphics/RenderCommand.hpp
        candy/core/include/candy/graphics/Renderer.hpp
        candy/core/include/candy/graphics/Renderer2D.hpp
        candy/core/include/candy/graphics/Renderer3D.hpp
        candy/core/include/candy/graphics/StorageBuffer.hpp
        candy/core/include/candy/graphics/UniformBuffer.hpp
        candy/core/include/candy/graphics/VertexArray.hpp
        candy/core/include/candy/graphics/VertexBuffer.hpp
        candy/core/include/candy/graphics/Vulkan.hpp
        candy/core/include/candy/graphics/vulkan/CommandBuffer.hpp
        candy/core/include/candy/graphics/vulkan/DeletionQueue.hpp
        candy/core/include/candy/graphics/vulkan/Image.hpp
        candy/core/include/candy/graphics/vulkan/ImageView.hpp
        candy/core/include/candy/graphics/vulkan/RenderPass.hpp
        candy/core/include/candy/graphics/vulkan/SwapChain.hpp
        candy/core/include/candy/graphics/vulkan/VulkanBuffer.hpp
        candy/core/include/candy/graphics/vulkan/VulkanDebugManager.hpp
        candy/core/include/candy/graphics/vulkan/device/VulkanDeviceManager.hpp
        candy/core/include/candy/graphics/vulkan/device/PhysicalDevice.hpp
        candy/core/include/candy/graphics/vulkan/device/LogicalDevice.hpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorSetLayout.hpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorLayoutCache.hpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorAllocatorPool.hpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp
        candy/core/include/candy/graphics/texture/ImageFormat.hpp
        candy/core/include/candy/graphics/model/ModelLoader.hpp
        candy/core/include/candy/graphics/shader/Shader.hpp
        candy/core/include/candy/graphics/color/ColorRGBA.hpp
        candy/core/include/candy/graphics/shader/processing/ShaderPostProcessor.hpp
        candy/core/include/candy/graphics/font/FontAtlasSettingsSerializer.hpp
        candy/core/include/candy/graphics/texture/Texture.hpp
        candy/core/include/candy/graphics/shader/ShaderLibrary.hpp
        candy/core/include/candy/graphics/shader/processing/ShaderPreProcessor.hpp
        candy/core/include/candy/graphics/font/MSDFSerializer.hpp
        candy/core/include/candy/graphics/shader/ShaderData.hpp
        candy/core/include/candy/graphics/texture/InternalTexture.hpp
        candy/core/include/candy/graphics/color/ColorRGBA8.hpp
        candy/core/include/candy/graphics/material/Material.hpp
        candy/core/include/candy/graphics/shader/ShaderLayout.hpp
        candy/core/include/candy/graphics/shader/config/ShaderSettings.hpp
        candy/core/include/candy/graphics/color/ColorBase.hpp
        candy/core/include/candy/graphics/color/ColorRGBA.inl
        candy/core/include/candy/graphics/model/Mesh.hpp
        candy/core/include/candy/graphics/texture/TextureManager.hpp
        candy/core/include/candy/graphics/shader/processing/ShaderSource.hpp
        candy/core/include/candy/graphics/font/Font.hpp
        candy/core/include/candy/graphics/font/MSDFData.hpp
        candy/core/include/candy/graphics/material/MaterialData.hpp
        candy/core/include/candy/graphics/model/MeshData.hpp
        candy/core/include/candy/graphics/font/FontManager.hpp
        candy/core/include/candy/graphics/shader/ShaderProperty.hpp
        candy/core/include/candy/graphics/shader/processing/ShaderParseObjects.hpp
        candy/core/include/candy/graphics/color/ColorBaseStaticData.hpp
        candy/core/include/candy/graphics/camera/PerspectiveCameraController.hpp
        candy/core/include/candy/graphics/camera/PerspectiveCamera.hpp
        candy/core/include/candy/graphics/camera/OrthographicCameraController.hpp
        candy/core/include/candy/graphics/camera/OrthographicCamera.hpp
        candy/core/include/candy/graphics/camera/EditorCamera.hpp
        candy/core/include/candy/graphics/camera/CameraController.hpp
        candy/core/include/candy/graphics/camera/CameraBase.hpp
        candy/core/include/candy/graphics/model/MeshPrimitive.hpp
        candy/core/include/candy/graphics/vulkan/CommandPool.hpp
        candy/core/include/candy/graphics/vulkan/VulkanPch.hpp
        candy/core/include/candy/graphics/shader/ShaderBufferManager.hpp
        candy/core/include/candy/graphics/vulkan/VulkanQueueManager.hpp
        candy/core/include/candy/graphics/FrameResources.hpp
        candy/core/include/candy/graphics/vulkan/RenderChain.hpp
        candy/core/include/candy/graphics/vulkan/RenderPassConfig.hpp
        candy/core/include/candy/graphics/shader/config/ShaderProfile.hpp
        candy/core/include/candy/graphics/shader/config/ShaderEnums.hpp
        candy/core/include/candy/graphics/shader/config/ShaderDynamicState.hpp
        candy/core/include/candy/graphics/shader/config/ShaderProfileSettings.hpp
        candy/core/include/candy/graphics/vulkan/RenderChainScheduler.hpp
        candy/core/include/candy/graphics/vulkan/RenderTarget.hpp)

set(CANDY_GRAPHICS_SOURCES candy/core/src/graphics/shader/ShaderData.cpp
        candy/core/src/graphics/texture/ImageFormat.cpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorAllocator.cpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorLayoutCache.cpp
        candy/core/src/graphics/vulkan/VulkanBuffer.cpp
        candy/core/src/graphics/texture/TextureManager.cpp
        candy/core/src/graphics/Renderer.cpp
        candy/core/src/graphics/RenderCommand.cpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorAllocatorPool.cpp
        candy/core/src/graphics/model/MeshData.cpp
        candy/core/src/graphics/VertexBuffer.cpp
        candy/core/src/graphics/texture/InternalTexture.cpp
        candy/core/src/graphics/shader/processing/ShaderPreProcessor.cpp
        candy/core/src/graphics/model/Mesh.cpp
        candy/core/src/graphics/Renderer2D.cpp
        candy/core/src/graphics/shader/processing/ShaderParseObjects.cpp
        candy/core/src/graphics/PixelBuffer.cpp
        candy/core/src/graphics/BufferLayout.cpp
        candy/core/src/graphics/shader/ShaderLibrary.cpp
        candy/core/src/graphics/vulkan/device/LogicalDevice.cpp
        candy/core/src/graphics/vulkan/VulkanDebugManager.cpp
        candy/core/src/graphics/shader/processing/ShaderSource.cpp
        candy/core/src/graphics/Renderer3D.cpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorBuilder.cpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorSetLayout.cpp
        candy/core/src/graphics/vulkan/Vulkan.cpp
        candy/core/src/graphics/GraphicsContext.cpp
        candy/core/src/graphics/vulkan/CommandBuffer.cpp
        candy/core/src/graphics/UniformBuffer.cpp
        candy/core/src/graphics/shader/config/ShaderSettings.cpp
        candy/core/src/graphics/model/ModelLoader.cpp
        candy/core/src/graphics/vulkan/device/PhysicalDevice.cpp
        candy/core/src/graphics/FrameBuffer.cpp
        candy/core/src/graphics/StorageBuffer.cpp
        candy/core/src/graphics/vulkan/device/VulkanDeviceManager.cpp
        candy/core/src/graphics/shader/ShaderProperty.cpp
        candy/core/src/graphics/vulkan/ImageView.cpp
        candy/core/src/graphics/shader/Shader.cpp
        candy/core/src/graphics/IndexBuffer.cpp
        candy/core/src/graphics/vulkan/SwapChain.cpp
        candy/core/src/graphics/texture/Texture.cpp
        candy/core/src/graphics/vulkan/RenderPass.cpp
        candy/core/src/graphics/shader/ShaderLayout.cpp
        candy/core/src/graphics/VertexArray.cpp
        candy/core/src/graphics/vulkan/Image.cpp
        candy/core/src/graphics/shader/processing/ShaderPostProcessor.cpp
        candy/core/src/graphics/vulkan/DeletionQueue.cpp
        candy/core/src/graphics/material/MaterialData.cpp
        candy/core/src/graphics/material/Material.cpp
        candy/core/src/graphics/font/MSDFSerializer.cpp
        candy/core/src/graphics/font/FontManager.cpp
        candy/core/src/graphics/font/FontAtlasSettingsSerializer.cpp
        candy/core/src/graphics/font/Font.cpp
        candy/core/src/graphics/color/ColorRGBA8.cpp
        candy/core/src/graphics/camera/PerspectiveCameraController.cpp
        candy/core/src/graphics/camera/PerspectiveCamera.cpp
        candy/core/src/graphics/camera/OrthographicCameraController.cpp
        candy/core/src/graphics/camera/OrthographicCamera.cpp
        candy/core/src/graphics/camera/EditorCamera.cpp
        candy/core/src/graphics/camera/CameraController.cpp
        candy/core/src/graphics/camera/CameraBase.cpp
        candy/core/src/graphics/model/MeshPrimitive.cpp
        candy/core/src/graphics/vulkan/CommandPool.cpp
        candy/core/src/graphics/FrameResources.cpp
        candy/core/src/graphics/vulkan/VulkanQueueManager.cpp
        candy/core/src/graphics/vulkan/RenderChain.cpp
        candy/core/src/graphics/vulkan/RenderPassConfig.cpp
        candy/core/src/graphics/shader/config/ShaderProfile.cpp
        candy/core/src/graphics/shader/config/ShaderDynamicState.cpp
        candy/core/src/graphics/shader/config/ShaderEnums.cpp
        candy/core/src/graphics/vulkan/RenderChainScheduler.cpp)

set(CANDY_GRAPHICS_FILES ${CANDY_GRAPHICS_HEADERS} ${CANDY_GRAPHICS_SOURCES})

set(CANDY_UI_FILES candy/core/include/candy/ui/UILayer.hpp
        candy/core/src/ui/UILayer.cpp
        candy/core/include/candy/ui/Gizmo.hpp
        candy/core/src/ui/Gizmo.cpp
        candy/core/include/candy/ui/GumLayer.hpp
        candy/core/src/ui/GumLayer.cpp)

set(CANDY_ECS_HEADERS candy/core/include/candy/ecs/BaseComponents.hpp
        candy/core/include/candy/ecs/Entity.hpp
        candy/core/include/candy/ecs/Scene.hpp
        candy/core/include/candy/ecs/SceneManager.hpp
        candy/core/include/candy/ecs/SceneSerializer.hpp
        candy/core/include/candy/ecs/System.hpp
        candy/core/include/candy/ecs/SystemScheduler.hpp
        candy/core/include/candy/ecs/TransformComponent.hpp
        candy/core/include/candy/ecs/MeshComponents.hpp)

set(CANDY_ECS_SOURCES candy/core/src/ecs/Entity.cpp
        candy/core/src/ecs/Scene.cpp
        candy/core/src/ecs/SceneManager.cpp
        candy/core/src/ecs/SceneSerializer.cpp
        candy/core/src/ecs/System.cpp
        candy/core/src/ecs/SystemScheduler.cpp
        candy/core/src/ecs/TransformComponent.cpp
        candy/core/src/ecs/MeshComponents.cpp)

set(CANDY_ECS_FILES ${CANDY_ECS_HEADERS} ${CANDY_ECS_SOURCES})

set(CANDY_APP_HEADERS candy/core/include/candy/app/Application.hpp
        candy/core/include/candy/app/Layer.hpp
        candy/core/include/candy/app/LayerStack.hpp
        candy/core/include/candy/app/Window.hpp)

set(CANDY_APP_SOURCES candy/core/src/app/Application.cpp
        candy/core/src/app/LayerStack.cpp
        candy/core/src/project/Project.cpp
        candy/core/src/project/ProjectSerializer.cpp
        candy/core/src/app/Window.cpp)

set(CANDY_APP_FILES ${CANDY_APP_HEADERS} ${CANDY_APP_SOURCES})

set(CANDY_PROJECT_HEADERS candy/core/include/candy/project/Project.hpp
        candy/core/include/candy/project/ProjectSerializer.hpp
        candy/core/include/candy/project/ProjectManager.hpp)

set(CANDY_PROJECT_SOURCES candy/core/src/project/Project.cpp
        candy/core/src/project/ProjectSerializer.cpp
        candy/core/src/project/ProjectManager.cpp)

set(CANDY_PROJECT_FILES ${CANDY_PROJECT_HEADERS} ${CANDY_PROJECT_SOURCES})



set(CANDY_CORE_FILES ${CANDY_BASE_FILES} ${CANDY_COLLECTIONS_FILES} ${CANDY_MATH_FILES} ${CANDY_NOISE_FILES} ${CANDY_UTILS_FILES} ${CANDY_EVENT_FILES} ${CANDY_GRAPHICS_FILES} ${CANDY_UI_FILES} ${CANDY_ECS_FILES} ${CANDY_APP_FILES} ${CANDY_PROJECT_FILES} candy/core/include/CandyPch.hpp candy/core/include/CandyPch.cpp)


set(CANDY_EDITOR_FILES candy/editor/include/editor/panels/ContentBrowserPanel.hpp
        candy/editor/include/editor/EditorLayer.hpp
        candy/editor/include/editor/panels/Viewport.hpp
        candy/editor/include/editor/panels/SceneHierarchyPanel.hpp
        candy/editor/include/editor/panels/DebugPanel.hpp
        candy/editor/src/EditorLayer.cpp
        candy/editor/src/panels/Viewport.cpp
        candy/editor/src/panels/SceneHierarchyPanel.cpp
        candy/editor/src/panels/DebugPanel.cpp
        candy/editor/src/panels/ContentBrowserPanel.cpp)



set(IM_GUI_SOURCES lib/imgui/imgui.h lib/imgui/imconfig.h lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_internal.h
        lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp lib/imgui/imstb_rectpack.h lib/imgui/imstb_textedit.h lib/imgui/imstb_truetype.h lib/imgui/backends/imgui_impl_vulkan.h
        lib/imgui/backends/imgui_impl_vulkan.cpp lib/imgui/backends/imgui_impl_glfw.h lib/imgui/backends/imgui_impl_glfw.cpp)

set(IM_GUIZMO_SOURCES lib/imguizmo/ImGuizmo.h lib/imguizmo/ImGuizmo.cpp lib/imguizmo/GraphEditor.h lib/imguizmo/GraphEditor.cpp lib/imguizmo/ImSequencer.h lib/imguizmo/ImSequencer.cpp
        lib/imguizmo/ImGradient.cpp lib/imguizmo/ImGradient.h lib/imguizmo/ImCurveEdit.cpp lib/imguizmo/ImCurveEdit.h lib/imguizmo/ImZoomSlider.h)

set(STB_LIB_FILES lib/stb/include/stb/stb_image.h
        lib/stb/include/stb/stb_truetype.h
        lib/stb/include/stb/stb_image_write.h)

set(VMA_LIB_FILES lib/vma/vk_mem_alloc.h)

set(CANDY_BUNDLED_LIB_FILES ${IM_GUI_SOURCES} ${IM_GUIZMO_SOURCES} ${STB_LIB_FILES} ${VMA_LIB_FILES})

set(CANDY_GUM_HEADERS candy/gum/include/gum/GumContext.hpp
        candy/gum/include/gum/GumInstance.hpp
        candy/gum/include/gum/GumTransform.hpp
        candy/gum/include/gum/GumTypes.hpp
        candy/gum/include/gum/GumRenderer.hpp
        candy/gum/include/gum/event/GumEvent.hpp
        candy/gum/include/gum/event/GumMouseEvent.hpp
        candy/gum/include/gum/event/GumKeyEvent.hpp
        candy/gum/include/gum/event/GumContextEvent.hpp
        candy/gum/include/gum/event/GumEventHandler.hpp
        candy/gum/include/gum/base/Node.hpp
        candy/gum/include/gum/shape/Shape.hpp
        candy/gum/include/gum/base/Root.hpp
        candy/gum/include/gum/shape/Rectangle.hpp
        candy/gum/include/gum/base/SceneGraph.hpp
        candy/gum/include/gum/base/Layout.hpp
        candy/gum/include/gum/render/RectRenderer.hpp
)

set(CANDY_GUM_SOURCES candy/gum/src/GumInstance.cpp
        candy/gum/src/GumTransform.cpp
        candy/gum/src/GumRenderer.cpp
        candy/gum/src/GumContext.cpp
        candy/gum/src/event/GumEvent.cpp
        candy/gum/src/event/GumMouseEvent.cpp
        candy/gum/src/event/GumKeyEvent.cpp
        candy/gum/src/event/GumContextEvent.cpp
        candy/gum/src/event/GumEventHandler.cpp
        candy/gum/src/base/Node.cpp
        candy/gum/src/base/Shape.cpp
        candy/gum/src/shape/Rectangle.cpp
        candy/gum/src/base/Root.cpp
        candy/gum/src/base/SceneGraph.cpp
        candy/gum/src/render/RectRenderer.cpp
)

set(CANDY_GUM_FILES ${CANDY_GUM_HEADERS} ${CANDY_GUM_SOURCES})

set(CANDY_ENGINE_FILES ${CANDY_CORE_FILES} ${CANDY_EDITOR_FILES} ${CANDY_GUM_FILES} ${CANDY_BUNDLED_LIB_FILES}
        candy/gum/include/gum/GumInstance.hpp candy/core/include/CandyEngine.hpp
        candy/core/include/CandyEngine.cpp
        candy/core/include/candy/engine/FileStructureValidator.hpp
)




option(CANDY_BUILD_SHARED "On- Build CandyEngine as a shared library. Off- Build CandyEngine as a static library." OFF)
option(CANDY_PROFILE "On- Enable profiling. Off- Disable profiling." OFF)
option(CANDY_ENABLE_LOGGING "On- Enable logging. Off- Disable logging." ON)



if (CANDY_BUILD_SHARED)
    add_library(CandyEngine SHARED ${CANDY_ENGINE_FILES})
else()
    add_library(CandyEngine STATIC ${CANDY_ENGINE_FILES})
endif()



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(CandyEngine PROPERTIES OUTPUT_NAME CandyEngineDebug)
    set_target_properties(CandyEngine PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(CandyEngine PROPERTIES CXX_STANDARD 23)
    target_compile_definitions(CandyEngine PRIVATE CANDY_DEBUG=1)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(CandyEngine PROPERTIES OUTPUT_NAME CandyEngineRelease)
    set_target_properties(CandyEngine PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(CandyEngine PROPERTIES CXX_STANDARD 23)
else()
    message("Some other build type.")
endif()

if (CANDY_PROFILE)
target_compile_definitions(CandyEngine PRIVATE CANDY_PROFILE)
endif()

if(CANDY_ENABLE_LOGGING)
    target_compile_definitions(CandyEngine PRIVATE CANDY_ENABLE_LOGGING)
endif()

target_compile_definitions(CandyEngine PRIVATE CANDY_DIRECTORY_INTERNALS="${INTERNAL_BINARY_RESOURCES_DIR}")
target_compile_definitions(CandyEngine PRIVATE CANDY_DIRECTORY_PROJECTS="${CMAKE_BINARY_DIR}/projects")

target_include_directories(CandyEngine PUBLIC candy/core/include)
target_include_directories(CandyEngine PUBLIC candy/editor/include)
target_include_directories(CandyEngine PUBLIC candy/gum/include)
target_include_directories(CandyEngine PUBLIC lib)
target_include_directories(CandyEngine PRIVATE lib/stb/include)
target_include_directories(CandyEngine PRIVATE lib/antlr/runtime/src)
target_include_directories(CandyEngine PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_include_directories(CandyEngine PRIVATE tools)


target_link_libraries(CandyEngine PRIVATE shaderc_shared ryml::ryml assimp::assimp antlr4_static)
target_link_libraries(CandyEngine PUBLIC spdlog::spdlog glfw Vulkan::Vulkan spirv-cross-c EnTT::EnTT FontAtlas)



add_executable(CandyEngineTest main.cpp)

set(VCPKG_ROOT "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin")
# This command will be executed after your executable is built and it will copy .dll files from the vcpkg dir to your output dir
#[[add_custom_command(TARGET CandyEngineTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${VCPKG_ROOT}
        $<TARGET_FILE_DIR:CandyEngineTest>)]]

add_dependencies(CandyEngineTest CopyInternal CopyTestProject)

target_link_libraries(CandyEngineTest PRIVATE CandyEngine)

