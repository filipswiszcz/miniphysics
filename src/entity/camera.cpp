#include <iostream>

#include <rush/entity/camera.hpp>

#include <glm/glm.hpp>

#pragma mark - Camera
#pragma region Camera {

glm::mat4 entity::Camera::get_look_at() {
    const glm::vec3 t(glm::normalize((this -> position + this -> target_position) - this -> position));
    const glm::vec3 r(glm::normalize(glm::cross(t, this -> up_position)));
    const glm::vec3 u(glm::cross(r, t));

    glm::mat4 res(1);
    res[0][0] = r.x;
    res[1][0] = r.y;
    res[2][0] = r.z;
    res[0][1] = u.x;
    res[1][1] = u.y;
    res[2][1] = u.z;
    res[0][2] = -t.x;
    res[1][2] = -t.y;
    res[2][2] = -t.z;
    res[3][0] = -glm::dot(r, this -> position);
    res[3][1] = -glm::dot(u, this -> position);
    res[3][2] = glm::dot(t, this -> position);

    return res;
}

void entity::Camera::set_target_position(const glm::vec3 position) {
    this -> target_position = position;
}

void entity::Camera::set_up_position(const glm::vec3 position) {
    this -> up_position = position;
}

void entity::Camera::set_mouse_x(const float value) {
    this -> mouse_x = value;
}

void entity::Camera::set_mouse_y(const float value) {
    this -> mouse_y = value;
}

void entity::Camera::set_yaw(const float value) {
    this -> yaw = value;
}

void entity::Camera::set_pitch(const float value) {
    this -> pitch = value;
}

void entity::Camera::set_speed(const float value) {
    this -> speed = value;
}

void entity::Camera::set_sensitivity(const float value) {
    this -> sensitivity = value;
}

#pragma endregion Camera }