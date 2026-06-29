#include "renderer/Camera2D.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace engine {

    void Camera2D::init(float sw, float sh) {
        screen_width = sw;
        screen_height = sh;
    }

    void Camera2D::setPosition(const glm::vec2& p) { position = p; }
    glm::vec2 Camera2D::getPosition() const { return position; }

    void Camera2D::setZoom(float z) { zoom = z; }
    float Camera2D::getZoom() const { return zoom; }

    glm::mat4 Camera2D::getProjectionMatrix() const { return glm::ortho(0.0f, screen_width, 0.0f, screen_height, -1.0f, 1.0f); }
    glm::mat4 Camera2D::getViewMatrix() const {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(-position, 0.0f));
        view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
        return view;
    }

}
