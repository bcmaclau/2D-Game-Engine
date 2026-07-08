#pragma once

#include <glm/glm.hpp>

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/Camera2D.h"
#include "scene/component/Sprite.h"
#include "scene/component/Transform.h"
#include "math/Vector.h"

namespace engine {

    class SpriteRenderer {
    public:
        SpriteRenderer() : VAO(0), VBO(0), EBO(0) {}
        ~SpriteRenderer() {}

        bool init();
        void beginFrame(Camera2D* camera);
        void draw(Component::Sprite* sprite, Component::Transform* transform);
        void endFrame();
        void shutdown();

    private:
        Shader shader;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

}