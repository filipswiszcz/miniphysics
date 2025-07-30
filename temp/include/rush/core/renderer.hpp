#ifndef RENDERER_H
#define RENDERER_H

#include <sstream>

#include <rush/core/scene.hpp>
#include <rush/mem/object_repository.hpp>
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

            mem::Repository repository;

            std::vector<std::shared_ptr<core::Scene>> scenes;

        public:

            Renderer();

            ~Renderer() = default;

            void bind();

            void draw();

            void release();

            void add_scene(const std::shared_ptr<core::Scene> &scene);

            void remove_scene(const std::shared_ptr<core::Scene> &scene);

    };

} // namespace core

#endif