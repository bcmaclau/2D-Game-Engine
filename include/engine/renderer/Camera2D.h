#pragma once

#include <glm/glm.hpp>

namespace engine {

    class Camera2D {
    public:
        Camera2D();
        ~Camera2D();

        void init(float sw, float sh);

        void setPosition(glm::vec2 p);
        glm::vec2 getPosition();

        void setZoom(float z);
        float getZoom();

        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();

    private:
        float screen_width;
        float screen_height;

        glm::vec2 position;
        float zoom;
    };

}
