cmake_minimum_required(VERSION 3.21)
project(Motueur)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Motueur main.cpp keyboard.cpp keyboard.hpp vertex.hpp mesh.cpp mesh.hpp time.cpp time.hpp
        material.cpp material.hpp shader.cpp shader.hpp texture.cpp texture.hpp skysphere.cpp skysphere.hpp Model.hpp Model.cpp)

include(cmake/glew.cmake)
include(cmake/assimp.cmake)

add_subdirectory(dep/glfw dep/glfw)

set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glfw/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)
set(STB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/stb)

target_include_directories(Motueur PRIVATE
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
)

add_library(imgui
        # Main Imgui files
        dep/imgui/imgui.cpp dep/imgui/imgui_draw.cpp
        dep/imgui/imgui_tables.cpp dep/imgui/imgui_widgets.cpp
        # SDL2+OpenGL-specific files
        dep/imgui/backends/imgui_impl_glfw.cpp
        dep/imgui/backends/imgui_impl_opengl3.cpp
        )

target_include_directories(imgui PUBLIC ${GLFW_INCLUDE_DIR})
target_include_directories(imgui PUBLIC dep/imgui/ dep/imgui/backends/)

# target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)


target_link_libraries(Motueur PRIVATE glfw opengl32 glew imgui assimp)



add_custom_target(copy_shaders COMMAND ${CMAKE_COMMAND}
-E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Motueur>/assets)

add_dependencies(Motueur copy_shaders)
