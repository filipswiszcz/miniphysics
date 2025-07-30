#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>

namespace core {

    class Shader {

        private:

            unsigned int id;

            std::string read_file(const std::string &filename);

            void compile(unsigned int &shader_id, const unsigned int type, const std::string &filename);
            void link(const unsigned int &vert_shader, const unsigned int frag_shader);

            unsigned int get_uniform_location(const std::string &name);            

        public:

            enum class Type : unsigned int {
                none = 0, boolean,
                i8, ui8,
                i16, ui16,
                i32, ui32, p32, // packed 32-bit int (16.16 integer)
                f16, f32, f64,
                vec2, vec3, vec4,
                ivec2, ivec3, ivec4,
                dvec2, dvec3, dvec4,
                mat2, mat3, mat4
            };

            Shader(const std::string &vert_filename, const std::string &frag_filename);
            ~Shader();

            void bind();

            void set_num(const std::string &name, const unsigned int &value);

            void set_num(const std::string &name, const int &value);

            void set_num(const std::string &name, const float &value);

            void set_num(const std::string &name, const unsigned int &count, const float *value);

            void set_mat4(const std::string &name, const float *mat, const unsigned int &count = 1, const bool &transpose = false);

            unsigned int get_id() {return id;}

    };

} // namespace core

#endif