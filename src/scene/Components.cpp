#include "scene/Components.h"

#include <iostream>

namespace engine {

    // --- Transform ---
    Vec2 Component::Transform::getPosition() const { return position; }
    void Component::Transform::setPosition(const Vec2& pos) { position = pos; }
    void Component::Transform::move(const Vec2& delta) { position += delta; }

    Vec2 Component::Transform::getScale() const { return scale; }
    void Component::Transform::setScale(const Vec2& s) { scale = s; }

    float Component::Transform::getRotation() const { return rotation; }
    void Component::Transform::setRotation(float r) { rotation = r; }
    void Component::Transform::rotate(float r) {
        rotation += r;
        while (rotation >= 360) { rotation -= 360; }
        while (rotation < 0) { rotation += 360; }
    }

    // --- Single Sprite ---
    Texture* Component::SingleSprite::getTexture() const { return texture; }
    void Component::SingleSprite::setTexture(const char* path) {
        if (assets) {
            texture = assets->loadTexture(path);
        }
    }

    Vec2 Component::SingleSprite::getDimensions() const { return dimensions; }
    void Component::SingleSprite::setDimensions(const Vec2& d) { dimensions = d; }

}
