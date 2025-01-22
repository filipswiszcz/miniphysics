#ifndef MESH_H
#define MESH_H

#include <iostream>
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
#include <glm/gtc/matrix_transform.hpp>

namespace entity {

    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
    };

    struct Material {
        std::string name;
        float shininess;
        glm::vec3 ambient, diffuse, specular, emissivity;
        float density, transparency;
        int illumination;
    };

    class Mesh {

        private:

            uint16_t id;
            
            std::vector<float> vertices;
            std::vector<uint32_t> indices;

            entity::Material material;

        public:

            Mesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices);
            ~Mesh() = default;

            uint16_t get_id() const {return id;}

            std::vector<float> get_vertices() const {return vertices;}

            std::vector<uint32_t> get_indices() const {return indices;}

            entity::Material get_material() const {return material;}

            void set_material(const entity::Material &material);

    };

    // class Mesh {

    //     private:

    //         std::vector<glm::vec3> vertices, normals;
    //         std::vector<glm::vec2> uvs;
    //         std::vector<unsigned int> indices;

    //         std::vector<glm::vec3> colors;

    //         unsigned int vao, vbo, ebo;

    //         unsigned int shader_program, texture;

    //     public:

    //         Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);

    //         ~Mesh();

    //         std::vector<glm::vec3> get_vertices() const {return vertices;}

    //         std::vector<glm::vec3> get_normals() const {return normals;}

    //         std::vector<glm::vec2> get_uvs() const {return uvs;}

    //         unsigned int &get_vao() {return vao;}

    //         unsigned int &get_vbo() {return vbo;}

    //         unsigned int &get_ebo() {return ebo;}

    //         unsigned int get_shader_program() const {return shader_program;}

    //         void set_shader_program(const unsigned int program);

    //         void set_texture(const unsigned int texture);

    // };

} // namespace entity

#endif