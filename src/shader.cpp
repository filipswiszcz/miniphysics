#include "shader.h"

// public

void Shader::create_program(std::string vertex_shader_path, std::string fragment_shader_path) {
    std::string vertex_shader_code = this -> read_file(vertex_shader_path);
    std::string fragment_shader_code = this -> read_file(fragment_shader_path);

    this -> ids[0] = this -> compile(GL_VERTEX_SHADER, vertex_shader_code);
    this -> ids[1] = this -> compile(GL_FRAGMENT_SHADER, fragment_shader_code);
    
    this -> program = glCreateProgram();
    glAttachShader(this -> program, this -> ids[0]);
    glAttachShader(this -> program, this -> ids[1]);
    glLinkProgram(this -> program);
#ifdef DEBUG
    // debug code
#endif
}

void Shader::set_vec3(std::string name, Vec3_t vec) {
    glUniform3f(glGetUniformLocation(this -> program, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::set_mat4(std::string name, Mat4_t mat) {
    glUniformMatrix4fv(glGetUniformLocation(this -> program, name.c_str()), 1, 0, &mat.m[0][0]);
}

// private

std::string Shader::read_file(std::string &path) {
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    ASSERT(file, "Failed to open shader file: %s", path.c_str());

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string code(size, '\0');
    ASSERT(file.read(&code[0], size), "Failed to read shader file: %s", path.c_str());
    return code;
}

uint32_t Shader::compile(uint32_t type, std::string &code) {
    uint32_t shader = glCreateShader(type);
    const char *source = code.c_str();
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
#ifdef DEBUG
    // debug code
#endif
    return shader;
}
