#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;

layout(location = 0) out vec2 out_uv;

uniform mat4 _transform;

void main() {
    gl_Position = _transform * vec4(in_position, 1.0);
    out_uv = in_uv;
}