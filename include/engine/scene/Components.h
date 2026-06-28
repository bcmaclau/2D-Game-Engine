#pragma once

#include <glm/glm.hpp>

#include "engine/scene/BaseGameObject.h"
#include "engine/renderer/AssetManager.h"
#include "engine/renderer/Texture.h"
#include <string>

namespace engine::component {

    enum class ID {
        TRANSFORM,
        SINGLE_SPRITE
    };

    class Transform {
    public:
        Transform() : position({ 0.0f, 0.0f }), scale({1.0f, 1.0f}), rotation(0.0f) {}
        ~Transform() {}

        glm::vec2 getPosition() const;
        void setPosition(const glm::vec2& pos);
        void move(const glm::vec2& delta);

        glm::vec2 getScale() const;
        void setScale(const glm::vec2& s);

        float getRotation() const;
        void setRotation(float r);
        void rotate(float r);

    private:
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
    };

    class SingleSprite {
        friend class engine::BaseGameObject;
    
    public:
        Texture* getTexture() const;
        void setTexture(const char* path);
        
        glm::vec2 getDimensions() const;
        void setDimensions(const glm::vec2& d);
        
    private:
        AssetManager* assets;
        Texture* texture;
        std::string texture_path;
        glm::vec2 dimensions;
    };

}
