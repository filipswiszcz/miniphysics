#pragma mark - Shader
#pragma region Shader {

#include <rush/core/shader.hpp>
extern "C" {
    #include <rush/util/log.h>
}

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif


std::string core::Shader::read_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        log_warn("%s not found!", filename.c_str()); return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void core::Shader::compile(unsigned int &shader_id, const unsigned int type, const std::string &filename) {
    std::string shader_code = this -> read_file(filename);
    if (strlen(shader_code.c_str()) == 0) {
        log_warn("%s shader file is empty!", filename.c_str()); return;
    }

    unsigned int shader = glCreateShader(type);
    const char *source_code = shader_code.c_str();
    glShaderSource(shader, 1, &source_code, nullptr);
    glCompileShader(shader);

    char info[512];
    int32_t status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shader, 512, nullptr, info);
        log_warn("%s shader did not compile: %s", filename.c_str(), info); return;
    }

    shader_id = shader;
}

void core::Shader::link(const unsigned int &vert_shader, const unsigned int frag_shader) {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    char info[512];
    int32_t status;
    glGetProgramiv(program, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(program, 512, nullptr, info);
        log_warn("shader did not link: %s", info); return;
    }

    glUseProgram(program);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

   this -> id = program;
}

unsigned int core::Shader::get_uniform_location(const std::string &name) {
    return glGetUniformLocation(this -> id, name.c_str());
}

core::Shader::Shader(const std::string &vert_filename, const std::string &frag_filename) {
    unsigned int vert_shader, frag_shader;
    this -> compile(vert_shader, GL_VERTEX_SHADER, vert_filename);
    this -> compile(frag_shader, GL_FRAGMENT_SHADER, frag_filename);
    this -> link(vert_shader, frag_shader);
}

core::Shader::~Shader() {
    glDeleteProgram(this -> id);
}

void core::Shader::bind() {
    glUseProgram(this -> id);
}

void core::Shader::set_num(const std::string &name, const unsigned int &value) {
    this -> bind(); glUniform1ui(this -> get_uniform_location(name), value);
}

void core::Shader::set_num(const std::string &name, const int &value) {
    this -> bind(); glUniform1i(this -> get_uniform_location(name), value);
}

void core::Shader::set_num(const std::string &name, const float &value) {
    this -> bind(); glUniform1f(this -> get_uniform_location(name), value);
}

void core::Shader::set_num(const std::string &name, const unsigned int &count, const float *value) {
    this -> bind(); glUniform1fv(this -> get_uniform_location(name), count, value);
}

void core::Shader::set_mat4(const std::string &name, const float *mat, const unsigned int &count, const bool &transpose) {
    this -> bind(); glUniformMatrix4fv(this -> get_uniform_location(name), count, (transpose ? GL_TRUE : GL_FALSE), mat);
}

#pragma endregion Shader}