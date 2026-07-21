#pragma once

#include <glm/glm.hpp>

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/Camera2D.h"
#include "scene/component/Sprite.h"
#include "scene/component/Transform.h"
#include "math/Vector.h"
#include "data_structures/PointerLinkedList.h"

namespace engine {

    class SpriteRenderer {
    public:
        SpriteRenderer() : VAO(0), VBO(0), EBO(0), camera_pos(glm::vec2(0.0f, 0.0f)) {}
        ~SpriteRenderer() {}

        bool init();
        void beginFrame(Camera2D* camera);
        void drawSprite(Component::Sprite* sprite, Component::Transform* transform);
        void drawUI(Component::Sprite* sprite, Component::Transform* transform);
        void drawInOrder(PointerLinkedList<Component::Sprite>* render_order);
        void endFrame();
        void shutdown();

    private:
        Shader shader;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        glm::vec2 camera_pos;
    };

}