#pragma mark Renderer
#pragma region Renderer {

#include <rush/core/renderer.hpp>

core::Renderer::Renderer() {}

core::Renderer::~Renderer() {}

void core::Renderer::draw() {
    for (auto mesh : this -> meshes) {
        mesh -> bind();
        mesh -> draw();
    }
}

void core::Renderer::release() {}

void core::Renderer::add_mesh(const entity::Mesh mesh) {
    this -> meshes.push_back(std::make_shared<entity::Mesh>(mesh));
}

#pragma endregion Renderer }