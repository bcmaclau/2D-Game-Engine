#include "engine/renderer/AssetManager.h"

namespace engine {

    AssetManager::AssetManager() {}
    AssetManager::~AssetManager() {}

    Texture* AssetManager::loadTexture(std::string path) {
        if (textures.find(path) != textures.end()) { return textures[path]; }
        
        Texture* tex = new Texture();
        tex->init(path.c_str());
        textures[path] = tex;
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
