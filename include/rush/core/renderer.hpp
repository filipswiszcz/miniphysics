#ifndef RENDERER_H
#define RENDERER_H

#include <sstream>

#include <rush/entity/mesh.hpp>
extern "C" {
    #include <rush/util/log.h>
}

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif
#include <glm/glm.hpp>

namespace core {

    class Renderer {

        private:

            std::vector<std::shared_ptr<entity::Mesh>> meshes;

        public:

            Renderer();

            ~Renderer();

            void draw();

            void release();

            void add_mesh(const entity::Mesh mesh);

    };

} // namespace core

#endif