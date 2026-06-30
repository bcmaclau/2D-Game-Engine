#pragma once

#include "scene/BaseGameObject.h"
#include "renderer/Texture.h"
#include "renderer/AssetManager.h"
#include "math/Vector.h"

namespace engine::Component {

    class SingleSprite {
        friend class engine::BaseGameObject;
    
    public:
        SingleSprite() : assets(nullptr), texture(nullptr), dimensions(Vec2(1.0f, 1.0f)) {}
        ~SingleSprite() {}

        Texture* getTexture() const;
        void setTexture(const char* path);
        
        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);
        
    private:
        AssetManager* assets;
        Texture* texture;
        Vec2 dimensions;
    };

}
