#include <iostream>
#include <fstream>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif

extern "C" {
    #include <rush/util/log.h>
}

#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

namespace util {

    // unsigned char *read_img_file(const char *filename);

    unsigned int temp_load_texture(const std::string& name);

} // namespace util

#endif