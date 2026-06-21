#pragma once

#include "engine/renderer/Texture.h"

#include <unordered_map>
#include <string>

namespace engine {

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        Texture* loadTexture(std::string path);
        void clear();

    private:
        std::unordered_map<std::string, Texture*> textures; 
    };

}
