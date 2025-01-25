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
#include <glm/gtc/quaternion.hpp>

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

    struct Model {
        std::string filepath;
        std::string name;
        std::vector<uint16_t> mesh_ids;
    };

    class Mesh {

        private:

            uint16_t id;
            
            std::vector<float> vertices;
            std::vector<uint32_t> indices;

            entity::Material material; // switch it to id

            uint32_t vao, vbo, ebo;

        public:

            Mesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices);
            ~Mesh() = default;

            uint16_t get_id() const {return id;}

            std::vector<float> get_vertices() const {return vertices;}
            std::vector<uint32_t> get_indices() const {return indices;}

            entity::Material get_material() const {return material;}
            void set_material(const entity::Material &material);

            uint32_t &get_vao() {return vao;}
            void set_vao(const uint32_t vao);
            uint32_t &get_vbo() {return vbo;}
            void set_vbo(const uint32_t vbo);
            uint32_t &get_ebo() {return ebo;}
            void set_ebo(const uint32_t ebo);

    };

    struct Transformation {
        glm::vec3 scale;
        glm::vec3 rotation_origin;
        glm::quat rotation;
        glm::vec3 translation;
    };

    struct Instance {
        uint16_t mesh_id;
        uint16_t transform_id;
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