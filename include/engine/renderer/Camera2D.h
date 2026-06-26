#pragma once

// TODO: make a wrapper class for vectors so users arent using glm
#include <glm/glm.hpp>

namespace engine {

    class Camera2D {
    public:
        Camera2D() : screen_width(800), screen_height(600), position({0.0f, 0.0f}), zoom(1.0f) {}
        ~Camera2D() {}

        void init(float sw, float sh);

        void setPosition(const glm::vec2& p);
        glm::vec2 getPosition() const;

        void setZoom(float z);
        float getZoom() const;

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix() const;

    private:
        float screen_width;
        float screen_height;

        glm::vec2 position;
        float zoom;
    };

}
