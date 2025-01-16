cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 11)

project(OpenGL_Template)

add_executable(${PROJECT_NAME}
main.cpp shaders.cpp)

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ext/glfw ${CMAKE_CURRENT_SOURCE_DIR}/../build/ext/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ext/glad ${CMAKE_CURRENT_SOURCE_DIR}/../build/ext/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ext/glm ${CMAKE_CURRENT_SOURCE_DIR}/../build/ext/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC ../ext/glfw/include
    PUBLIC ../ext/glad/include
    PUBLIC ../ext/glm/glm
    PUBLIC ../ext/imgui
    PUBLIC ../ext/imgui/backends
)

target_link_directories(${PROJECT_NAME}
PUBLIC ../ext/glfw/src
PUBLIC ../ext/glad/src
PUBLIC ../ext/glm/glm)

target_sources(${PROJECT_NAME} PRIVATE
    ../ext/imgui/imgui.cpp
    ../ext/imgui/imgui_draw.cpp
    ../ext/imgui/imgui_demo.cpp
    ../ext/imgui/imgui_widgets.cpp
    ../ext/imgui/imgui_tables.cpp
    ../ext/imgui/backends/imgui_impl_glfw.cpp
    ../ext/imgui/backends/imgui_impl_opengl3.cpp
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw glad glm)