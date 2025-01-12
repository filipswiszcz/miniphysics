#include <rush/util/resource_loader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#pragma mark Resource_Loader
#pragma region Resource_Loader {

unsigned int util::temp_load_texture(const std::string &filename) {
    unsigned int temp_texture;
    glGenTextures(1, &temp_texture);
    glBindTexture(GL_TEXTURE_2D, temp_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels_k;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *img = stbi_load(filename.c_str(), &width, &height, &channels_k, 0);
    if (!img) {
        log_warn("failed to load img texture.");
    } else {
        int frmt, in_frmt;
        switch (channels_k) {
            case 1:
                frmt = GL_RED;
                in_frmt = GL_RED;
            case 3:
                frmt = GL_RGB;
                in_frmt = GL_RGB;
            case 4:
                frmt = GL_RGBA;
                in_frmt = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, in_frmt, width, height, 0, frmt, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(img);

    return temp_texture;
}

void util::load_mesh(const std::string &filename, float vertices[]) {
    std::vector<glm::vec3> vertices_t, normals_t;
    std::vector<glm::vec2> uvs_t;

    std::vector<float> vertices_f;

    std::ifstream file(filename);
    if (!file) {
        log_warn("mesh file: %s not found", filename.c_str()); return;
    }

    std::string line;
    while(std::getline(file, line)) {
        if (line.starts_with("v ")) {
            glm::vec3 vertex;
            sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            vertices_t.push_back(vertex);
        } else if (line.starts_with("vn")) {
            glm::vec3 normal;
            sscanf(line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            normals_t.push_back(normal);
        } else if (line.starts_with("vt")) {
            glm::vec2 uv;
            sscanf(line.c_str(), "vt %f %f", &uv.x, &uv.y);
            uvs_t.push_back(uv);
        } else if (line.starts_with("f")) {
            std::regex pattern("([a-z]) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+)");
            std::smatch match;
            if (!std::regex_match(line, match, pattern)) continue; // 2 3  5 6  8 9
            // log_info("%s", (match[2].str()).c_str());

            // fuck
            glm::vec3 ver_elem_a = vertices_t[std::stoi(match[2].str()) - 1];
            glm::vec3 ver_elem_b = vertices_t[std::stoi(match[5].str()) - 1];
            glm::vec3 ver_elem_c = vertices_t[std::stoi(match[8].str()) - 1];
            glm::vec2 uv_elem_a = uvs_t[std::stoi(match[3].str()) - 1];
            glm::vec2 uv_elem_b = uvs_t[std::stoi(match[6].str()) - 1];
            glm::vec2 uv_elem_c = uvs_t[std::stoi(match[9].str()) - 1];

            for (int j = 0; j < 3; j++) vertices_f.push_back(ver_elem_a[j]);
            for (int j = 0; j < 2; j++) vertices_f.push_back(uv_elem_a[j]);

            for (int j = 0; j < 3; j++) vertices_f.push_back(ver_elem_b[j]);
            for (int j = 0; j < 2; j++) vertices_f.push_back(uv_elem_b[j]);

            for (int j = 0; j < 3; j++) vertices_f.push_back(ver_elem_c[j]);
            for (int j = 0; j < 2; j++) vertices_f.push_back(uv_elem_c[j]);

            // for (int i = 0; i < 10; i += 2) {
            //     if (i == 0 || i == 3 || i == 6 || i == 9) continue;
            //     glm::vec3 ver_elem = vertices_t[std::stoi(match[i + 1].str()) - 1];
            //     log_debug("%f %f %f", ver_elem[0], ver_elem[1], ver_elem[2]);
            //     glm::vec2 uv_elem = uvs_t[std::stoi(match[i + 2].str()) - 1];
            //     for (int j = 0; j < 3; j++) vertices_f.push_back(ver_elem[j]);
            //     for (int j = 0; j < 2; j++) vertices_f.push_back(uv_elem[j]);
            // }
            // log_info("\n");
        }
    }

    log_debug("vector size %d", vertices_f.size());

    std::copy(vertices_f.begin(), vertices_f.end(), vertices);
}

void util::load_obj(const std::string& name, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals) {
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;

    std::ifstream file(name);
    if (!file) {
        std::cout << "file not found" << std::endl; return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.starts_with("v ")) {
            glm::vec3 vertex;
            sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (line.starts_with("vt")) {
            glm::vec2 uv;
            sscanf(line.c_str(), "vt %f %f", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (line.starts_with("vn")) {
            glm::vec3 normal;
            sscanf(line.c_str(), "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (line.starts_with("f")) {
            std::string vertex_a, vertex_b, vertex_c;
            unsigned int vertex_id[3], uv_id[3], normal_id[3];
            std::regex pattern("([a-z]) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+)");
            std::smatch match;
            if (std::regex_match(line, match, pattern)) {
                vertex_id[0] = std::stoi(match[2].str());
                uv_id[0] = std::stoi(match[3].str());
                normal_id[0] = std::stoi(match[4].str());
                vertex_id[1] = std::stoi(match[5].str());
                uv_id[1] = std::stoi(match[6].str());
                normal_id[1] = std::stoi(match[7].str());
                vertex_id[2] = std::stoi(match[8].str());
                uv_id[2] = std::stoi(match[9].str());
                normal_id[2] = std::stoi(match[10].str());
            }
            vertex_indices.push_back(vertex_id[0]);
            vertex_indices.push_back(vertex_id[1]);
            vertex_indices.push_back(vertex_id[2]);
            uv_indices.push_back(uv_id[0]);
            uv_indices.push_back(uv_id[1]);
            uv_indices.push_back(uv_id[2]);
            normal_indices.push_back(normal_id[0]);
            normal_indices.push_back(normal_id[1]);
            normal_indices.push_back(normal_id[2]);
        }
    }

    file.close();

    for (unsigned int i = 0; i < vertex_indices.size(); i++) {
        unsigned int vertex_id = vertex_indices[i];
        unsigned int uv_id = uv_indices[i];
        unsigned int normal_id = normal_indices[i];

        glm::vec3 vertex = temp_vertices[vertex_id - 1];
        glm::vec2 uv = temp_uvs[uv_id - 1];
        glm::vec3 normal = temp_normals[normal_id - 1];

        vertices.push_back(vertex);
        uvs.push_back(uv);
        normals.push_back(normal);
    }
}

#pragma endregion Resource_Loader }