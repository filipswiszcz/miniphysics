#version 410 core
out vec4 post_color;

in vec2 proc_texture_pos;

uniform sampler2D temp_texture;

void main() {
    post_color = texture(temp_texture, proc_texture_pos);
}