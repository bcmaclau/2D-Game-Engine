#pragma once

#include "renderer/Texture.h"
#include "data_structures/Vector.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

namespace engine {

    struct SpriteInfo {
        Vec2 dimensions;
        float u0, v0, u1, v1, frame_width;
        int layer, width, height, current_frame, interval, interval_acc;
    };

    class AssetManager {
        friend class BaseScene;

    public:
        AssetManager() : texture_array_id(0), max_tex_width(0), max_tex_height(0) {}
        ~AssetManager() {}

        // used for the batch renderer
        void addSpriteDirectory(const char* dir, bool recursive);
        void loadSprites();
        SpriteInfo* getSprite(const char* path);

        void printSprites() {
            for (std::string s : sprite_paths) {
                std::cout << s <<  std::endl;
            }
        }

        void shutdown();

    private:
        std::vector<std::string> sprite_paths;
        unsigned int texture_array_id;
        int max_layers;
        int max_tex_width, max_tex_height;
        std::unordered_map<std::string, SpriteInfo*> sprite_lookup;
    };

}
