#version 410 core

layout (location = 0) in vec2 vertex;

void main() {
    gl_Position = vec4(vertex.x, vertex.y, 0.0f, 1.0f);
    gl_PointSize = 8.0f;
}