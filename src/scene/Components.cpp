#include "engine/scene/Components.h"

#include <iostream>

namespace engine {

    // --- Transform ---
    glm::vec2 component::Transform::getPosition() const { return position; }
    void component::Transform::setPosition(const glm::vec2& pos) { position = pos; }
    void component::Transform::move(const glm::vec2& delta) { position += delta; }

    glm::vec2 component::Transform::getScale() const { return scale; }
    void component::Transform::setScale(const glm::vec2& s) { scale = s; }

    float component::Transform::getRotation() const { return rotation; }
    void component::Transform::setRotation(float r) { rotation = r; }
    void component::Transform::rotate(float r) {
        rotation += r;
        while (rotation >= 360) { rotation -= 360; }
    }

    // --- Single Sprite ---
    Texture* component::SingleSprite::getTexture() const { return texture; }
    void component::SingleSprite::setTexture(const char* path) {
        if (assets) {
            texture = assets->loadTexture(path);
        }
    }

    glm::vec2 component::SingleSprite::getDimensions() const { return dimensions; }
    void component::SingleSprite::setDimensions(const glm::vec2& d) { dimensions = d; }

}
