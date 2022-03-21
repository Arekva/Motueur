#version 330 core

out vec3 out_color;
layout(location = 0) in vec2 in_uv;

uniform sampler2D _texture;

void main() {
    out_color = texture(_texture, in_uv).rgb;
}