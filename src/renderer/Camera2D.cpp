#include "renderer/Camera2D.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace engine {

    void Camera2D::init(unsigned int sw, unsigned int sh, float suv) {
        screen_width = sw;
        screen_height = sh;
        screen_units_v = suv;
        screen_units_h = (((float)screen_width) / ((float)screen_height)) * screen_units_v;
        half_suv = screen_units_v / 2.0f;
        half_suh = screen_units_h / 2.0f;
        half_sw = ((float)screen_width) / 2.0f;
        half_sh = ((float)screen_height) / 2.0f;
        pixels_per_unit = ((float)screen_width) / screen_units_v;
    }

    void Camera2D::setPosition(const glm::vec2& p) { position = p; }
    glm::vec2 Camera2D::getPosition() const { return position; }

    void Camera2D::setZoom(float z) { zoom = z; }
    float Camera2D::getZoom() const { return zoom; }

    glm::mat4 Camera2D::getProjectionMatrix() const { return glm::ortho(-half_suh, half_suh, -half_suv, half_suv, 0.1f, 100.1f); }
    glm::mat4 Camera2D::getViewMatrix() const { return glm::lookAt(glm::vec3(position, 100.0f), glm::vec3(position, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); }

    glm::vec2 Camera2D::toScreenCoords(const glm::vec2 wc) const { return glm::vec2(half_sw, half_sh) + ((wc - position) * pixels_per_unit); }
    glm::vec2 Camera2D::toWorldCoords(const glm::vec2 sc) const { return ((sc - glm::vec2(half_sw, half_sh)) / pixels_per_unit) + position; }

}
