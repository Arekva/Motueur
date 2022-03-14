cmake_minimum_required(VERSION 3.21)
project(Motueur)

set(CMAKE_CXX_STANDARD 14)

add_executable(Motueur main.cpp keyboard.cpp keyboard.hpp vertex.hpp mesh.cpp mesh.hpp camera.hpp)

include(cmake/glew.cmake)

add_subdirectory(dep/glfw dep/glfw)
add_subdirectory(dep/SDL dep/SDL)

set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glfw/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/glm)
set(SDL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dep/SDL/include)

target_include_directories(Motueur PRIVATE
        ${GLFW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
	    ${SDL_INCLUDE_DIR}
)

target_link_libraries(Motueur PRIVATE SDL2-static glfw SDL2main opengl32 glew)