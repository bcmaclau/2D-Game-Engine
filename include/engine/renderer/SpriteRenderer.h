#pragma once

#include <glm/glm.hpp>

#include "engine/renderer/Shader.h"
#include "engine/renderer/Texture.h"
#include "engine/renderer/Camera2D.h"


namespace engine {

    class SpriteRenderer {
    public:
        SpriteRenderer();
        ~SpriteRenderer();

        bool init();
        void beginFrame(Camera2D* camera);
        void draw(Texture* texture, glm::vec2 position, glm::vec2 size, float rotation = 0.0f);
        void endFrame();
        void shutdown();

    private:
        Shader shader;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

}