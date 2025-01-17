#pragma mark - Object
#pragma region Object {

#include <iostream>

#include <rush/entity/object.hpp>

#include <glm/glm.hpp>


void entity::Object::set_mesh(const entity::Mesh mesh) {
    this -> mesh = mesh;
}

#pragma endregion Object }