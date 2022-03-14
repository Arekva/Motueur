#pragma once

#include "glm/glm.hpp"

struct Vertex {
public:
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec4 tangent;
};