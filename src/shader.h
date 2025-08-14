#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <fstream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#else
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif

#include "common.h"
#include "math.h"

class Shader {
public:
    uint32_t get_program() {return program;}
    void create_program(std::string vertex_shader_path, std::string fragment_shader_path);
    void set_vec3(std::string name, Vec3_t vec);
    void set_mat4(std::string name, Mat4_t mat);
private:
    uint32_t ids[2]; // [0] = vert, [1] = frag
    uint32_t program;
    std::string read_file(std::string &path);
    uint32_t compile(uint32_t type, std::string &code);
};

#endif // !__SHADER_H__
