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
    public:
        static unsigned int texture_array_id;
        static int num_layers;
        static int max_tex_width, max_tex_height;

        static void addSpriteDirectory(const char* dir, bool recursive);
        static void loadSprites();
        static SpriteInfo* getSprite(const char* path);

        static void reset();
    
    private:
        AssetManager() {}
        
        static std::vector<std::string> sprite_paths;
        static std::unordered_map<std::string, SpriteInfo*> sprite_lookup;
    };

}
