#ifndef OBJECT_H
#define OBJECT_H

#include <rush/entity/entity.hpp>
#include <rush/entity/mesh.hpp>

namespace entity {

    enum Type {

    };

    class Object : public Entity {

            entity::Mesh mesh;

            bool is_visible = true;

        public:

            entity::Mesh get_mesh() {return mesh;}

            void set_mesh(const entity::Mesh mesh);

    };

} // namespace entity

#endif