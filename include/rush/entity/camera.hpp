#include <rush/entity/entity.hpp>

#ifndef CAMERA_H
#define CAMERA_H

namespace entity {

    class Camera : public Entity {

            glm::vec3 target_position, up_position;

            float mouse_x, mouse_y;
            float yaw = -90.0f, pitch = 0.0f;

            float speed = 2.0f, sensitivity = 0.2f;

        public:

            glm::mat4 get_look_at();

            glm::vec3 get_target_position() {return target_position;}

            void set_target_position(const glm::vec3 position);

            glm::vec3 get_up_position() {return up_position;}

            void set_up_position(const glm::vec3 position);

            float get_mouse_x() {return mouse_x;}

            void set_mouse_x(const float value);

            float get_mouse_y() {return mouse_y;}

            void set_mouse_y(const float value);

            float get_yaw() {return yaw;}

            void set_yaw(const float value);

            float get_pitch() {return pitch;}

            void set_pitch(const float value);

            float get_speed() {return speed;}

            void set_speed(const float value);

            float get_sensitivity() {return sensitivity;}

            void set_sensitivity(const float value);

    };

} // namespace entity

#endif