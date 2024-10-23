#include <rush/util/shader_loader.hpp>

#pragma mark - Shader_Loader
#pragma region Shader_Loader {

std::string util::read_file(const std::string& name) {
    std::ifstream file(name);
    if (!file) {
        std::cout << "file not found" << std::endl; return "";
    }
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return code;
}

GLuint util::compile(const std::string& code, GLenum type) {
    GLuint shader = glCreateShader(type);
    const char* source = code.c_str();

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    char info[512];
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        std::cout << "shader did not compile: " << info << std::endl; return 0;
    }

    return shader;
}

GLuint util::link(GLuint vertex_shader, GLuint frag_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);

    char info[512];
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        glGetProgramInfoLog(program, 512, NULL, info);
        std::cout << "shader did not link: " << info << std::endl; return 0;
    }

    return program;
}

#pragma endregion Shader_Loader }