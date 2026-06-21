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
        glm::vec2 getPosition();
        void move(glm::vec2 delta);

        void setSize(glm::vec2 s);
        glm::vec2 getSize();

        void setRotation(float r);
        float getRotation();
        void rotate(float r);

        // --- Active ---
        void setActive(bool a);
        bool isActive();

        // --- Texture ---
        void setTexture(const char* path);
        Texture* getTexture();

        // --- Bounding Box ---
        glm::vec2 getMin(); // bottom left
        glm::vec2 getMax(); // top right

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
