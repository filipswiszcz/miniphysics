#ifndef OBJECT_REPOSITORY_H
#define OBJECT_REPOSITORY_H

#include <atomic>
#include <map>

#include <rush/object/mesh.hpp>

namespace mem {

    class Repository {

        private:

            std::atomic<uint16_t> LAST_MESH_ID = 0;

            std::map<uint16_t, object::Mesh> meshes;

            // std::map<std::string, object::Model> models;

        public:

            Repository() = default;
            ~Repository() = default;

            object::Mesh get_mesh(const uint16_t id) {return meshes[id];}
            void add_mesh(const object::Mesh &mesh);

    };

}

#endif