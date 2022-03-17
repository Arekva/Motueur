cmake_minimum_required(VERSION 3.21)
project(Motueur)

set(CMAKE_CXX_STANDARD 14)

add_executable(Motueur main.cpp keyboard.cpp keyboard.hpp vertex.hpp mesh.cpp mesh.hpp camera.hpp)

include(cmake/glew.cmake)

add_subdirectory(dep/glfw dep/glfw)

set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glfw/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/imgui)

target_include_directories(Motueur PRIVATE
        ${GLFW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
)

target_link_libraries(Motueur PRIVATE glfw opengl32 glew)