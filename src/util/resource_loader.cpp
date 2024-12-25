#include <rush/util/resource_loader.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#pragma mark Resource_Loader
#pragma region Resource_Loader {

unsigned int util::temp_load_texture(const std::string& filename) {
    unsigned int temp_texture;
    glGenTextures(1, &temp_texture);
    glBindTexture(GL_TEXTURE_2D, temp_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels_k;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *img = stbi_load("resources/textures/witcher_wallpaper.jpg", &width, &height, &channels_k, 0);
    if (!img) {
        log_warn("failed to load img texture.");
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(img);

    return temp_texture;
}

#pragma endregion Resource_Loader }