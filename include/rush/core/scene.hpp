#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <rush/entity/object.hpp>

namespace core {

    class Scene {

        private:

            std::vector<std::shared_ptr<entity::Object>> objects;

            std::vector<entity::Vertex> vertices;
            unsigned int vao, vbo, ebo;

            bool visible = false;

        public:

            Scene() = default;

            ~Scene() = default;

            void bind();

            void update();

            void draw();

            void add_object(const std::shared_ptr<entity::Object> &object);

            void remove_object(const std::shared_ptr<entity::Object> &object);

    };

} // namespace core

#endif