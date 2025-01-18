#ifndef MODEL_H
#define MODEL_H

#include <vector>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>

namespace entity {

    class Model {

        private:

            std::vector<glm::vec3> vertices, normals;
            std::vector<glm::vec2> uvs;
            std::vector<unsigned int> indices;

            unsigned int vao, vbo, ebo;

        public:

            Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);

    };

} // namespace entity

#endif