#pragma once

#include <glm/glm.hpp>

namespace engine {

    class Camera2D {
    public:
        Camera2D() : screen_width(800), screen_height(600), position({0.0f, 0.0f}), zoom(1.0f) {}
        ~Camera2D() {}

        void init(unsigned int sw, unsigned int sh, float suv);

        void setPosition(const glm::vec2& p);
        glm::vec2 getPosition() const;

        void setZoom(float z);
        float getZoom() const;

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix() const;

        glm::vec2 toScreenCoords(const glm::vec2 wc) const;
        glm::vec2 toWorldCoords(const glm::vec2 sc) const;

    private:
        float screen_units_h, screen_units_v;
        float half_suh, half_suv;
        unsigned int screen_width, screen_height;
        float half_sw, half_sh;
        float pixels_per_unit;

        glm::vec2 position;
        float zoom;
    };

}
