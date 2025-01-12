#version 410 core
out vec4 post_color;

in vec2 proc_texture_pos;

uniform sampler2D texture_t;

void main() {
    post_color = texture(texture_t, proc_texture_pos);
}