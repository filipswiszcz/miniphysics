#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>

extern "C" {
    #include <rush/util/log.h>
}

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>

namespace util {

    // unsigned char *read_img_file(const char *filename);

    unsigned int temp_load_texture(const std::string& name);

    void load_obj(const std::string& name, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals);

} // namespace util

#endif