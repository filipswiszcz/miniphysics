#ifndef OBJECT_H
#define OBJECT_H

#include <rush/entity/entity.hpp>
#include <rush/entity/mesh.hpp>

namespace entity {

    enum Type {
        
    };

    class Object : public Entity {

            std::shared_ptr<entity::Mesh> mesh;

            bool visible = true;

        public:

            Object() = default;

            std::shared_ptr<entity::Mesh> get_mesh() const {return mesh;}

            void set_mesh(const std::shared_ptr<entity::Mesh> &mesh);

            bool is_visible() const {return visible;}

            void set_visible(const bool state);

    };

} // namespace entity

#endif