#pragma mark - Mesh
#pragma region Mesh {

#include <iostream>

#include <rush/entity/mesh.hpp>
extern "C" {
    #include <rush/util/log.h>
}

entity::Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals) {
    this -> vertices = vertices;
    this -> uvs = uvs;
    this -> normals = normals;
}

entity::Mesh::~Mesh() {}

void entity::Mesh::bind() {
    std::vector<entity::Vertex> uninted_vertices;
    for (int i = 0; i < this -> vertices.size(); i++) {
        Vertex vertex = {this -> vertices[i], this -> uvs[i], this -> normals[i]};
        uninted_vertices.push_back(vertex);
    }

    glGenVertexArrays(1, &this -> vao);
    glGenBuffers(1, &this -> vbo);
    // glGenBuffers(1, &this -> ebo);

    glBindVertexArray(this -> vao);
    glBindBuffer(GL_ARRAY_BUFFER, this -> vbo);
    glBufferData(GL_ARRAY_BUFFER, uninted_vertices.size() * sizeof(Vertex), uninted_vertices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, this -> indices.size() * sizeof(unsigned int), &this -> indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (2 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (5 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // glBindVertexArray(0);
}

void entity::Mesh::draw() {
    glUseProgram(this -> shader_program);
    glBindVertexArray(this -> vao);
    // glDrawElements(GL_TRIANGLES, static_cast<int>(this -> indices.size()), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, (this -> vertices.size() * 2 + this -> uvs.size()));
    glBindVertexArray(0);
}

void entity::Mesh::set_shader_program(const unsigned int program) {
    this -> shader_program = program;
}

void entity::Mesh::set_texture(const unsigned int texture) {
    this -> texture = texture;
}

#pragma endregion Mesh }