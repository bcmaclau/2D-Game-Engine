#pragma once

#include "scene/BaseGameObject.h"
#include "renderer/AssetManager.h"
#include "renderer/Texture.h"
#include "math/Vector.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SINGLE_SPRITE,
        BOX_COLLIDER
    };

    class Transform {
    public:
        Transform() : position({ 0.0f, 0.0f }), scale({1.0f, 1.0f}), rotation(0.0f) {}
        ~Transform() {}

        Vec2 getPosition() const;
        void setPosition(const Vec2& pos);
        void move(const Vec2& delta);

        Vec2 getScale() const;
        void setScale(const Vec2& s);

        float getRotation() const;
        void setRotation(float r);
        void rotate(float r);

    private:
        Vec2 position;
        Vec2 scale;
        float rotation;
    };

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

    class BoxCollider {
        friend class engine::BaseGameObject;

    public:
        BoxCollider() : dimensions(Vec2(1.0f, 1.0f)) {}
        ~BoxCollider() {}

        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);

        Vec2 getMin() const;
        Vec2 getMax() const;

    private:
        Transform* transform;
        Vec2 dimensions;
        float half_x, half_y;
    };

}
