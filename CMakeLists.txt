cmake_minimum_required(VERSION 3.26)
project(CandyEngine)
set(CMAKE_CXX_STANDARD 23)
find_package(Vulkan REQUIRED)

add_subdirectory(lib/spdlog)
add_subdirectory(lib/glfw)
add_subdirectory(lib/shaderc)
add_subdirectory(lib/SPIRV-Cross)
add_subdirectory(lib/entt)
add_subdirectory(lib/antlr)



set(IM_GUI_SOURCES lib/imgui/imgui.h lib/imgui/imconfig.h lib/imgui/imgui.cpp lib/imgui/imgui_demo.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_internal.h
        lib/imgui/imgui_tables.cpp lib/imgui/imgui_widgets.cpp lib/imgui/imstb_rectpack.h lib/imgui/imstb_textedit.h lib/imgui/imstb_truetype.h lib/imgui/backends/imgui_impl_vulkan.h
        lib/imgui/backends/imgui_impl_vulkan.cpp lib/imgui/backends/imgui_impl_glfw.h lib/imgui/backends/imgui_impl_glfw.cpp)

set(IM_GUIZMO_SOURCES lib/imguizmo/ImGuizmo.h lib/imguizmo/ImGuizmo.cpp lib/imguizmo/GraphEditor.h lib/imguizmo/GraphEditor.cpp lib/imguizmo/ImSequencer.h lib/imguizmo/ImSequencer.cpp
        lib/imguizmo/ImGradient.cpp lib/imguizmo/ImGradient.h lib/imguizmo/ImCurveEdit.cpp lib/imguizmo/ImCurveEdit.h lib/imguizmo/ImZoomSlider.h
        candy/core/include/candy/graphics/camera/EditorCamera.hpp
        candy/core/include/candy/graphics/camera/CameraBase.hpp
        candy/core/src/graphics/camera/CameraBase.cpp
        candy/core/include/candy/graphics/camera/OrthographicCameraController.hpp
        candy/core/src/graphics/camera/OrthographicCameraController.cpp)

add_library(CandyEngine SHARED candy/core/include/CandyPch.hpp candy/core/include/candy/base/Assert.hpp candy/core/include/candy/base/Base.hpp candy/core/include/candy/base/CandyConcepts.hpp candy/core/include/candy/base/PlatformDetection.hpp candy/core/include/candy/base/Log.hpp candy/core/include/candy/base/Instrumentor.hpp candy/core/include/candy/base/MouseCodes.hpp candy/core/include/candy/base/KeyCodes.hpp candy/core/include/candy/base/RawBuffer.hpp candy/core/include/candy/base/UUID.hpp candy/core/include/candy/base/PrimitiveTypes.hpp candy/core/src/base/Log.cpp candy/core/src/base/UUID.cpp candy/core/include/CandyPch.cpp
        candy/core/include/candy/collections/Array2D.hpp candy/core/include/candy/collections/Array3D.hpp
        candy/core/include/candy/math/Math.hpp candy/core/include/candy/math/direction/Direction2.hpp candy/core/include/candy/math/direction/Direction3.hpp candy/core/include/candy/math/vector/Vector2Base.hpp candy/core/include/candy/math/vector/Vector3Base.hpp candy/core/include/candy/math/vector/Vector4Base.hpp candy/core/include/candy/math/vector/VectorBase.hpp candy/core/include/candy/math/vector/VectorBaseStaticData.hpp candy/core/include/candy/math/vector/VectorExpression.hpp candy/core/include/candy/math/vector/VectorOperations.hpp candy/core/include/candy/math/Vector.hpp candy/core/include/candy/math/Range.hpp candy/core/include/candy/math/Limit.hpp candy/core/include/candy/math/MathOps.hpp candy/core/include/candy/math/Rectangle.hpp candy/core/include/candy/math/matrix/base/MatrixExpression.hpp candy/core/include/candy/math/matrix/base/MatrixBase.hpp candy/core/include/candy/math/matrix/base/LayoutPolicy.hpp candy/core/include/candy/math/matrix/specialization/Matrix4RowMajor.hpp candy/core/include/candy/math/matrix/specialization/Matrix4ColumnMajor.hpp candy/core/include/candy/math/matrix/specialization/Matrix3.hpp candy/core/include/candy/math/Matrix.hpp candy/core/include/candy/math/quaternion/QuaternionBase.hpp candy/core/include/candy/math/Quaternion.hpp candy/core/include/candy/math/Random.hpp candy/core/src/math/direction/Direction3.cpp candy/core/src/math/direction/Direction2.cpp candy/core/include/candy/math/Direction.hpp candy/core/src/math/matrix/Matrix3.cpp candy/core/src/math/matrix/Matrix4ColumnMajor.cpp candy/core/src/math/matrix/Matrix4RowMajor.cpp candy/core/include/candy/math/Random.inl candy/core/include/candy/math/vector/Vector3Base.inl candy/core/include/candy/math/vector/Vector2Base.inl candy/core/include/candy/math/vector/Vector4Base.inl candy/core/include/candy/math/quaternion/QuaternionBase.inl
        candy/core/include/candy/event/Event.hpp candy/core/include/candy/event/EventDispatcher.hpp candy/core/include/candy/event/IEventListener.hpp candy/core/include/candy/event/Input.hpp candy/core/include/candy/event/KeyEvent.hpp candy/core/include/candy/event/MouseEvent.hpp candy/core/include/candy/event/WindowEvent.hpp candy/core/src/event/Input.cpp candy/core/src/event/KeyEvent.cpp candy/core/src/event/MouseEvent.cpp candy/core/src/event/WindowEvent.cpp candy/core/include/candy/event/Events.hpp
        candy/core/include/candy/noise/PerlinNoise.hpp candy/core/src/noise/PerlinNoise.cpp
        candy/core/include/candy/utils/FileUtils.hpp candy/core/include/candy/utils/FrameTime.hpp candy/core/include/candy/utils/Stopwatch.hpp candy/core/src/utils/FileUtils.cpp candy/core/src/utils/FrameTime.cpp candy/core/src/utils/Stopwatch.cpp
        candy/core/include/candy/app/Application.hpp candy/core/include/candy/app/Window.hpp candy/core/src/app/Window.cpp candy/core/src/app/Application.cpp
        candy/core/include/candy/graphics/BufferLayout.hpp candy/core/include/candy/graphics/Color.hpp candy/core/include/candy/graphics/GraphicsContext.hpp candy/core/include/candy/graphics/IndexBuffer.hpp candy/core/include/candy/graphics/Renderer.hpp candy/core/include/candy/graphics/shader/Shader.hpp candy/core/include/candy/graphics/shader/ShaderData.hpp candy/core/include/candy/graphics/shader/ShaderLibrary.hpp candy/core/include/candy/graphics/UniformBuffer.hpp candy/core/include/candy/graphics/VertexArray.hpp candy/core/include/candy/graphics/VertexBuffer.hpp candy/core/include/candy/graphics/Vulkan.hpp candy/core/include/candy/graphics/vulkan/CommandBuffer.hpp candy/core/include/candy/graphics/vulkan/RenderPass.hpp candy/core/include/candy/graphics/vulkan/SwapChain.hpp candy/core/include/candy/graphics/vulkan/VulkanBuffer.hpp candy/core/include/candy/graphics/vulkan/VulkanDebugManager.hpp candy/core/include/candy/graphics/vulkan/VulkanInstance.hpp candy/core/include/candy/graphics/vulkan/pipeline/Pipeline.hpp candy/core/include/candy/graphics/vulkan/pipeline/PipelineLayout.hpp candy/core/include/candy/graphics/vulkan/device/LogicalDevice.hpp candy/core/include/candy/graphics/vulkan/device/PhysicalDevice.hpp candy/core/include/candy/graphics/vulkan/device/VulkanDeviceManager.hpp candy/core/include/candy/graphics/color/ColorBase.hpp candy/core/src/graphics/BufferLayout.cpp candy/core/src/graphics/GraphicsContext.cpp candy/core/src/graphics/IndexBuffer.cpp candy/core/src/graphics/Renderer.cpp candy/core/src/graphics/shader/Shader.cpp candy/core/src/graphics/shader/ShaderData.cpp candy/core/src/graphics/shader/ShaderLibrary.cpp candy/core/src/graphics/VertexArray.cpp candy/core/src/graphics/VertexBuffer.cpp candy/core/src/graphics/vulkan/CommandBuffer.cpp candy/core/src/graphics/vulkan/RenderPass.cpp candy/core/src/graphics/vulkan/SwapChain.cpp candy/core/src/graphics/vulkan/Vulkan.cpp candy/core/src/graphics/vulkan/VulkanBuffer.cpp candy/core/src/graphics/vulkan/VulkanDebugManager.cpp candy/core/src/graphics/vulkan/VulkanInstance.cpp candy/core/src/graphics/vulkan/pipeline/Pipeline.cpp candy/core/src/graphics/vulkan/pipeline/PipelineLayout.cpp candy/core/src/graphics/vulkan/device/LogicalDevice.cpp candy/core/src/graphics/vulkan/device/PhysicalDevice.cpp candy/core/src/graphics/vulkan/device/VulkanDeviceManager.cpp lib/vma/vk_mem_alloc.h lib/vke/descriptor_allocator.h lib/vke/descriptor_allocator.cpp
        candy/core/include/candy/ecs/System.hpp candy/core/include/candy/ecs/SystemScheduler.hpp candy/core/include/candy/ecs/Scene.hpp candy/core/include/candy/ecs/SceneManager.hpp candy/core/include/candy/ecs/BaseComponents.hpp candy/core/include/candy/ecs/Entity.hpp candy/core/src/ecs/System.cpp candy/core/src/ecs/SystemScheduler.cpp candy/core/src/ecs/SceneManager.cpp candy/core/src/ecs/Scene.cpp candy/core/include/candy/app/Layer.hpp candy/core/include/candy/graphics/camera/Camera.hpp candy/core/include/candy/graphics/camera/CameraController.hpp candy/core/src/graphics/camera/Camera.cpp candy/core/src/graphics/camera/CameraController.cpp candy/core/src/graphics/UniformBuffer.cpp candy/core/include/candy/utils/IDManager.hpp candy/core/include/candy/graphics/Texture.hpp candy/core/src/graphics/Texture.cpp candy/core/include/candy/graphics/color/ColorRGBA8.hpp candy/core/src/graphics/color/ColorRGBA8.cpp candy/core/include/candy/graphics/color/ColorRGBA.hpp candy/core/src/graphics/color/ColorRGBA.cpp candy/core/include/candy/graphics/vulkan/ImageView.hpp candy/core/src/graphics/vulkan/ImageView.cpp candy/core/include/candy/graphics/vulkan/Image.hpp candy/core/src/graphics/vulkan/Image.cpp candy/core/src/graphics/shader/processing/ShaderParseObjects.cpp candy/core/src/graphics/shader/processing/ShaderPreProcessor.cpp candy/core/src/graphics/shader/processing/ShaderSource.cpp candy/core/include/candy/graphics/shader/processing/ShaderParseObjects.hpp candy/core/include/candy/graphics/shader/processing/ShaderPreProcessor.hpp candy/core/include/candy/graphics/shader/processing/ShaderSource.hpp candy/core/include/candy/graphics/shader/processing/ShaderPostProcessor.hpp candy/core/src/graphics/shader/processing/ShaderPostProcessor.cpp candy/core/include/candy/graphics/material/Material.hpp tools/grammer/GLSLListener.cpp tools/grammer/GLSLParser.cpp tools/grammer/GLSLVisitor.cpp tools/grammer/GLSLVisitor.h tools/grammer/GLSLLexer.cpp tools/grammer/GLSLBaseVisitor.h tools/grammer/GLSLBaseVisitor.cpp tools/grammer/GLSLBaseListener.cpp candy/core/include/candy/graphics/vulkan/descriptor/DescriptorAllocator.hpp candy/core/src/graphics/vulkan/descriptor/DescriptorAllocator.cpp candy/core/include/candy/graphics/vulkan/descriptor/DescriptorLayoutCache.hpp candy/core/src/graphics/vulkan/descriptor/DescriptorLayoutCache.cpp candy/core/include/candy/graphics/vulkan/descriptor/DescriptorBuilder.hpp candy/core/src/graphics/vulkan/descriptor/DescriptorBuilder.cpp candy/core/include/candy/graphics/shader/ShaderLayout.hpp candy/core/include/candy/app/LayerStack.hpp candy/core/src/app/LayerStack.cpp candy/core/include/candy/graphics/vulkan/DeletionQueue.hpp candy/core/src/graphics/vulkan/DeletionQueue.cpp candy/core/include/candy/graphics/vulkan/descriptor/DescriptorSetLayout.hpp candy/core/src/graphics/vulkan/descriptor/DescriptorSetLayout.cpp
        candy/core/src/graphics/shader/ShaderLayout.cpp candy/core/src/graphics/material/Material.cpp candy/core/include/candy/ui/UILayer.hpp candy/core/src/ui/UILayer.cpp
        candy/core/include/candy/graphics/RenderCommand.hpp
        candy/core/src/graphics/RenderCommand.cpp
        candy/editor/include/editor/EditorLayer.hpp
        candy/editor/src/EditorLayer.cpp
        candy/editor/include/editor/panels/ContentBrowserPanel.hpp
        candy/core/include/candy/app/Project.hpp
        candy/core/include/candy/utils/Version.hpp
        candy/core/src/utils/Version.cpp
        candy/core/src/app/Project.cpp
        candy/editor/src/panels/ContentBrowserPanel.cpp
        candy/core/include/candy/graphics/FrameBuffer.hpp
        candy/core/src/graphics/FrameBuffer.cpp
        candy/gum/include/gum/widget/Button.hpp
        candy/editor/include/editor/panels/Viewport.hpp
        candy/editor/src/panels/Viewport.cpp
        candy/gum/include/gum/base/GumRenderer.hpp
        candy/gum/include/gum/widget/WidgetBase.hpp
        candy/core/include/candy/graphics/Renderer2D.hpp
        candy/core/include/candy/graphics/StorageBuffer.hpp
        candy/core/src/graphics/StorageBuffer.cpp
        candy/core/include/candy/graphics/vulkan/descriptor/DescriptorAllocatorPool.hpp
        candy/core/src/graphics/vulkan/descriptor/DescriptorAllocatorPool.cpp
        candy/core/include/candy/graphics/material/MaterialData.hpp
        candy/core/src/graphics/material/MaterialData.cpp
        candy/core/include/candy/graphics/shader/ShaderProperty.hpp
        candy/core/src/graphics/shader/ShaderProperty.cpp
        candy/core/include/candy/graphics/model/Mesh.hpp
        candy/gum/include/gum/base/GumObject.hpp
        candy/gum/src/gum/base/GumObject.cpp
        candy/gum/include/gum/base/GumTree.hpp
        candy/gum/include/gum/base/GumShape.hpp
        candy/gum/src/gum/base/GumShape.cpp
        candy/core/include/candy/graphics/camera/OrthographicCamera.hpp
        candy/core/src/graphics/camera/OrthographicCamera.cpp
        candy/gum/src/gum/base/GumRenderer.cpp
        candy/gum/src/gum/base/GumTree.cpp
        candy/gum/include/gum/base/GumStyle.hpp
        candy/gum/include/gum/base/GumLayout.hpp
        candy/core/src/graphics/model/Mesh.cpp
        candy/core/include/candy/graphics/Renderer3D.hpp
        candy/core/src/graphics/Renderer3D.cpp
        candy/core/src/graphics/Renderer2D.cpp
        candy/core/include/candy/graphics/model/MeshData.hpp
        candy/core/src/graphics/model/MeshData.cpp
        candy/editor/include/editor/panels/SceneHierarchyPanel.hpp
        candy/editor/src/panels/SceneHierarchyPanel.cpp
        candy/editor/include/editor/panels/DebugPanel.hpp
        candy/editor/src/panels/DebugPanel.cpp
        candy/core/include/candy/math/ray/Ray3.hpp
        candy/core/include/candy/graphics/PixelBuffer.hpp
        candy/core/src/graphics/PixelBuffer.cpp
        ${IM_GUI_SOURCES}
        ${IM_GUIZMO_SOURCES}
        candy/core/src/graphics/camera/EditorCamera.cpp
        candy/core/include/candy/graphics/ImageFormat.hpp
        candy/core/src/graphics/ImageFormat.cpp
)





target_include_directories(CandyEngine PUBLIC candy/core/include)
target_include_directories(CandyEngine PUBLIC candy/editor/include)
target_include_directories(CandyEngine PUBLIC candy/gum/include)
target_include_directories(CandyEngine PUBLIC lib)
target_include_directories(CandyEngine PUBLIC lib/stb/include)
target_include_directories(CandyEngine PUBLIC lib/antlr/runtime/src)
target_include_directories(CandyEngine PRIVATE tools)
#target_include_directories(CandyEngine PUBLIC lib/imgui)
target_link_libraries(CandyEngine PUBLIC spdlog::spdlog glfw Vulkan::Vulkan shaderc_shared spirv-cross-c EnTT antlr4_static)


add_executable(CandyEngineTest main.cpp)

target_link_libraries(CandyEngineTest PRIVATE CandyEngine)