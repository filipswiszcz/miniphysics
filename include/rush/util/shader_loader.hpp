#include <iostream>
#include <fstream>
#include <string>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#endif

#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

namespace util {

    std::string read_file(const std::string& name);

    GLuint compile(const std::string& code, GLenum type);

    GLuint link(GLuint vertex_shader, GLuint frag_shader);
    
} // namespace util

#endif