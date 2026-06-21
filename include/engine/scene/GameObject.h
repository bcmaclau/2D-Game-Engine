#pragma once

#include <glm/glm.hpp>
#include "engine/renderer/Texture.h"
#include "engine/renderer/AssetManager.h"

namespace engine {

    class GameObject {
    public:
        GameObject();
        virtual ~GameObject();
        
        virtual void onInit();
        virtual void onUpdate(float dt);

        // --- Transform ---
        void setPosition(glm::vec2 pos);
        glm::vec2 getPosition() const;
        void move(glm::vec2 delta);

        void setSize(glm::vec2 s);
        glm::vec2 getSize() const;

        void setRotation(float r);
        float getRotation() const;
        void rotate(float r);

        // --- Active ---
        void setActive(bool a);
        bool isActive() const;

        // --- Texture ---
        void setTexture(const char* path);
        Texture* getTexture() const;

        // --- Bounding Box ---
        glm::vec2 getMin() const; // bottom left
        glm::vec2 getMax() const; // top right

    private:
        glm::vec2 position;
        glm::vec2 size;
        float rotation;
        
        Texture* texture;
        
        friend class Scene;
        bool active;
        size_t scene_index;
        AssetManager* assets;
    };

}
