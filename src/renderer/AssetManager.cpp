#include "engine/renderer/AssetManager.h"

#include "engine/core/Paths.h"

#include <iostream>

namespace engine {

    Texture* AssetManager::loadTexture(const char* path) {
        std::string s_path(path);
        std::string r_path = Paths::resolve(s_path);
        auto it = textures.find(r_path);
        if (it != textures.end()) { return it->second; }
        
        Texture* tex = new Texture();
        if (!tex->init(r_path.c_str())) {
            std::cout << "Failed to load texture :" << path << std::endl;
            delete tex;
            return nullptr;
        }
        textures[r_path] = tex;
        return tex;
    }

    void AssetManager::clear() {
        for (auto it = textures.begin(); it != textures.end(); it++) {
            it->second->shutdown();
            delete it->second;
        }
        textures.clear();
    }

}
