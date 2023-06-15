project(Sugar)

set(SUGAR_SOURCES src/EditorLayer.hpp src/EditorLayer.cpp src/panels/ContentBrowserPanel.hpp src/panels/SceneHierarchyPanel.hpp src/panels/SceneHierarchyPanel.cpp src/panels/ContentBrowserPanel.cpp)

add_library(${PROJECT_NAME} STATIC ${SUGAR_SOURCES})

FILE(COPY Resources DESTINATION "${CMAKE_BINARY_DIR}/sugar")
FILE(COPY SandboxProject DESTINATION "${CMAKE_BINARY_DIR}/sugar")

target_link_libraries(${PROJECT_NAME} PUBLIC Sandbox)



