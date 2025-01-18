#pragma mark - Object
#pragma region Object {

#include <iostream>

#include <rush/entity/object.hpp>

#include <glm/glm.hpp>


void entity::Object::set_mesh(const std::shared_ptr<entity::Mesh> &mesh) {
    this -> mesh = mesh;
}

void entity::Object::set_visible(const bool state) {
    this -> visible = state;
}

#pragma endregion Object }