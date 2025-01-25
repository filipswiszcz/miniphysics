#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <rush/mem/object_repository.hpp>
#include <rush/object/mesh.hpp>

namespace core {

    class Scene {

        private:

            std::vector<uint16_t> meshes_ids;

            bool coolored = false;
            bool visible = false;

            glm::vec3 gravity;

        public:

            Scene() = default;
            ~Scene() = default;

            void bind(const mem::Repository &repository);

            void update();

            void draw(const mem::Repository &repository);

            void add_mesh_id(const uint16_t id);

            // void remove_object(const std::shared_ptr<entity::Object> &object);

    };

} // namespace core

#endif