#ifndef GRID_H
#define GRID_H

#include <vector>

#include <rush/core/shader.hpp>
extern "C" {
    #include <rush/util/log.h>
}

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace world {

    class Grid {

        private:

            unsigned int vao, vbo, ebo;

            std::vector<float> vertices = {
                -1.0f, -1.0f,
                -1.0f,  1.0f,
                1.0f,  1.0f,
                1.0f, -1.0f
            };
            std::vector<unsigned int> indices = {
                0, 1, 2,
                0, 2, 3
            };

            std::shared_ptr<core::Shader> shader;

        public:

            enum class Plane {
                xz, xy,
                yz, yx
            };

            Grid() = default;
            ~Grid() = default;

            void bind();

            void draw(const glm::mat4 &view, const glm::mat4 &projection, const glm::vec2 &near_far = {0.01f, 1000.0f});

            void set_shader(const std::shared_ptr<core::Shader> shader);

    };

} // namespace world

#endif