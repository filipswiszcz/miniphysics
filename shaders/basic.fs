#version 410 core
in vec2 proc_texture_pos;
in vec3 proc_color_pos;

out vec4 proc_color;

uniform sampler2D texture_t;
uniform bool is_coloring;

void main() {
    if (!is_coloring) proc_color = texture(texture_t, proc_texture_pos);
    else proc_color = vec4(proc_color_pos, 1.0);
}