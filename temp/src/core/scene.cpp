#pragma mark Scene
#pragma region Scene {

#include <rush/core/scene.hpp>


void core::Scene::bind(const mem::Repository &repository) {
    for (int i = 0; i < this -> meshes_ids.size(); i++) {
        object::Mesh mesh = repository.get_mesh(this -> meshes_ids.at(i));
        glGenVertexArrays(1, &mesh.get_vao());
        glGenBuffers(1, &mesh.get_vbo());

        glBindVertexArray(mesh.get_vao());
        glBindBuffer(GL_ARRAY_BUFFER, mesh.get_vbo());
        glBufferData(GL_ARRAY_BUFFER, mesh.get_vertices().size() * sizeof(float), mesh.get_vertices().data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }
}

void core::Scene::update() {}

void core::Scene::draw(const mem::Repository &repository) {
    for (int i = 0; i < this -> meshes_ids.size(); i++) {

    }
}

void core::Scene::add_mesh_id(const uint16_t id) {
    this -> meshes_ids.push_back(id);
}

// void core::Scene::bind() {
//     for (int i = 0; i < this -> objects.size(); i++) {
//         for (int j = 0; j < this -> objects[i] -> get_mesh() -> get_vertices().size(); j++) {
//             entity::Vertex vertex = {
//                 this -> objects[i] -> get_mesh() -> get_vertices()[j],
//                 this -> objects[i] -> get_mesh() -> get_uvs()[j],
//                 this -> objects[i] -> get_mesh() -> get_normals()[j]
//             };
//             this -> vertices.push_back(vertex);
//         }
//     }

//     glGenVertexArrays(1, &this -> vao);
//     glGenBuffers(1, &this -> vbo);

//     glBindVertexArray(this -> vao);
//     glBindBuffer(GL_ARRAY_BUFFER, this -> vbo);
//     glBufferData(GL_ARRAY_BUFFER, this -> vertices.size() * sizeof(entity::Vertex), this -> vertices.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(entity::Vertex), (void*) 0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(entity::Vertex), (void*) (3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(entity::Vertex), (void*) (5 * sizeof(float)));
// }

// void core::Scene::update() {}

// void core::Scene::draw() {
//     for (int i = 0; i < this -> objects.size(); i++) {
//         glUseProgram(this -> objects[i] -> get_mesh() -> get_shader_program()); // later i should group object by same shader program and create vao for each of them

//         glm::mat4 model = glm::mat4(1.0f);
//         model = glm::translate(model, this -> objects[i] -> get_position());
//         glUniformMatrix4fv(glGetUniformLocation(this -> objects[i] -> get_mesh() -> get_shader_program(), "model"), 1, GL_FALSE, &model[0][0]);

//         glBindVertexArray(this -> vao);
//         glDrawArrays(GL_TRIANGLES, 0, this -> vertices.size());
//     }
// }

// void core::Scene::add_object(const std::shared_ptr<entity::Object> &object) {
//     this -> objects.push_back(object);
// }

// void core::Scene::remove_object(const std::shared_ptr<entity::Object> &object) {
//     this -> objects.erase(std::remove(this -> objects.begin(), this -> objects.end(), object), this -> objects.end());
// }

#pragma endregion Scene }