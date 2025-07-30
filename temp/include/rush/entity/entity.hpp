#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

namespace entity {

    class Entity {

        protected:

            glm::vec3 position;

        public:

            glm::vec3 get_position() {return position;}

            void set_position(glm::vec3 position);

    };

} // namespace entity

#endif