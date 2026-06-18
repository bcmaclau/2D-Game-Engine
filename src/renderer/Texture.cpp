#include <glad/glad.h>
#include <stb/stb_image.h>

#include <engine/renderer/Texture.h>

#include <iostream>

namespace engine {

    Texture::Texture() : id(0), width(0), height(0), channels(0) {}
    Texture::~Texture() {
        if (id) {
            glDeleteTextures(1, &id);
        }
    }

    bool Texture::init(const char* path) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        stbi_set_flip_vertically_on_load(true);
        
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
        if (!data) {
            std::cout << "Failed to load texture. path: " << path << std::endl;
            return false;
        }

        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    void Texture::bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    int Texture::getWidth() { return width; }
    int Texture::getHeight() { return height; }

}
