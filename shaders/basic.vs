#version 410 core
layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec2 texture_pos;
layout (location = 2) in vec3 color_pos;

out vec2 proc_texture_pos;
out vec3 proc_color_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool is_coloring;

void main() {
    gl_Position = projection * view * model * vec4(vert_pos.x, vert_pos.y, vert_pos.z, 1.0);
    proc_texture_pos = vec2(texture_pos.x, 1.0 - texture_pos.y);
    proc_color_pos =  color_pos;
}