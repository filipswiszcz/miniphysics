#pragma mark - Grid
#pragma region Grid {

#include <rush/world/grid.hpp>


void world::Grid::bind() {
    glGenVertexArrays(1, &this -> vao);
    glGenBuffers(1, &this -> vbo);
    glGenBuffers(1, &this -> ebo);
    
    glBindVertexArray(this -> vao);

    glBindBuffer(GL_ARRAY_BUFFER, this -> vbo);
    glBufferData(GL_ARRAY_BUFFER, this -> vertices.size() * sizeof(float), this -> vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this -> indices.size() * sizeof(unsigned int), this -> indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void world::Grid::draw(const glm::mat4 &view, const glm::mat4 &projection, const glm::vec2 &near_far) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    this -> shader -> bind();
    this -> shader -> set_num("u_nearfar", 2, glm::value_ptr(near_far));
    this -> shader -> set_mat4("view", glm::value_ptr(view));
    this -> shader -> set_mat4("projection", glm::value_ptr(projection));

    glBindVertexArray(this -> vao);
    glBindBuffer(GL_ARRAY_BUFFER, this -> vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this -> ebo);
    glDrawElements(GL_TRIANGLES, this -> indices.size(), GL_UNSIGNED_INT, 0);
}

void world::Grid::set_shader(const std::shared_ptr<core::Shader> shader) {
    this -> shader = shader;
}

#pragma endregion Grid }