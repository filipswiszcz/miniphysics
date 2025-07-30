#ifndef TERRAIN_H
#define TERRAIN_H

extern "C" {
    #include <rush/util/log.h>
}

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>

namespace world { // 14.3

    class Terrain {

        private:

            unsigned int vao, vbo;

        public:

            void initialize();

            void draw();

    };

} // namespace world

#endif