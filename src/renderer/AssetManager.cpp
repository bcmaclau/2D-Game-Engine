#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/AssetManager.h"

#include "core/Paths.h"

#include <stb/stb_image.h>

#include <iostream>
#include <filesystem>

namespace engine {

    unsigned int AssetManager::texture_array_id = 0;
    int AssetManager::num_layers = 0;
    int AssetManager::max_tex_width = 0;
    int AssetManager::max_tex_height = 0;
    std::vector<std::string> AssetManager::sprite_paths;
    std::unordered_map<std::string, SpriteInfo*> AssetManager::sprite_lookup;

    void AssetManager::addSpriteDirectory(const char* dir, bool recursive) {
        if (recursive) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(Paths::resolve(std::string(dir)))) {
                if (!entry.is_regular_file()) continue;

                std::string ext = entry.path().extension().string();
                if (ext == ".png") { sprite_paths.push_back(entry.path().string()); }
            }
        }
        else {
            for (const auto& entry : std::filesystem::directory_iterator(Paths::resolve(std::string(dir)))) {
                if (!entry.is_regular_file()) continue;

                std::string ext = entry.path().extension().string();
                if (ext == ".png") { sprite_paths.push_back(entry.path().string()); }
            }
        }
    }

    void AssetManager::loadSprites() {
        for (std::string path : sprite_paths) {
            int w, h, ch;
            if (!stbi_info(path.c_str(), &w, &h, &ch)) {
                std::cerr << "Failed to read header: " << path << std::endl;
                continue;
            }
            if (w > max_tex_width) { max_tex_width = w; }
            if (h > max_tex_height) { max_tex_height = h; }
        }
        num_layers = sprite_paths.size();

        glGenTextures(1, &texture_array_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array_id);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, max_tex_width, max_tex_height, sprite_paths.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        stbi_set_flip_vertically_on_load(1);

        for (int i = 0; i < sprite_paths.size(); i++) {
            int w, h, ch;
            unsigned char* data = stbi_load(sprite_paths[i].c_str(), &w, &h, &ch, 4);
            if (!data) {
                std::cerr << "Failed to load: " << sprite_paths[i] << std::endl;
                continue;
            }

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, w, h, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

            sprite_lookup[sprite_paths[i]] = new SpriteInfo { Vec2(1.0f, 1.0f), 0.0f, 0.0f, (float)w / max_tex_width, (float)h / max_tex_height, (float)w / max_tex_width, i, w, h, 0, 0, 0 };

            stbi_image_free(data);
        }

        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    SpriteInfo* AssetManager::getSprite(const char* path) {
        std::string s_path(path);
        std::string r_path = Paths::resolve(s_path);
        auto it = sprite_lookup.find(r_path);
        if (it == sprite_lookup.end()) { std::cerr << "Failed to find sprite: " << r_path << std::endl; return {}; }
        return sprite_lookup[r_path];
    }

    void AssetManager::reset() {
        for (auto it = sprite_lookup.begin(); it != sprite_lookup.end(); it++) {
            delete it->second;
        }
        sprite_lookup.clear();

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        glDeleteTextures(1, &texture_array_id);
    }

}
