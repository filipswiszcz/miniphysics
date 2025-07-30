#ifndef MESH_F_H
#define MESH_F_H

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

namespace object {

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

            object::Material material; // switch it to id

            uint32_t vao, vbo, ebo;

        public:

            Mesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices);
            ~Mesh() = default;

            uint16_t get_id() const {return id;}

            std::vector<float> get_vertices() const {return vertices;}
            std::vector<uint32_t> get_indices() const {return indices;}

            object::Material get_material() const {return material;}
            void set_material(const object::Material &material);

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
        uint32_t transform_id;
    };

} // namespace object

#endif