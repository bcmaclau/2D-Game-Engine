#include "engine/renderer/AssetManager.h"

#include "engine/core/Paths.h"

namespace engine {

    AssetManager::AssetManager() {}
    AssetManager::~AssetManager() {}

    Texture* AssetManager::loadTexture(std::string path) {
        std::string r_path = Paths::resolve(path);
        if (textures.find(r_path) != textures.end()) { return textures[r_path]; }
        
        Texture* tex = new Texture();
        tex->init(r_path.c_str());
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
