#ifndef MESH_H
#define MESH_H

#include <vector>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
    #include <GLFW/glfw3.h>
#endif

#include <glm/glm.hpp>

namespace entity {

    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
    };

    class Mesh {

        private:

            std::vector<glm::vec3> vertices, normals;
            std::vector<glm::vec2> uvs;
            std::vector<unsigned int> indices;

            std::vector<glm::vec3> colors;

            unsigned int vao, vbo, ebo;

            unsigned int shader_program, texture;

        public:

            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);

            ~Mesh();

            void bind();

            void draw();

            void set_shader_program(const unsigned int program);

            void set_texture(const unsigned int texture);

    };

} // namespace entity

#endif