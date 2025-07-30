#pragma mark Object_repository
#pragma region Object_repository {

#include <rush/mem/object_repository.hpp>


void mem::Repository::add_mesh(const object::Mesh &mesh) {
    this -> meshes[this -> LAST_MESH_ID++] = mesh;
    log_debug("current_mesh_id: %d", this -> LAST_MESH_ID);
}

#pragma endregion Object_repository }