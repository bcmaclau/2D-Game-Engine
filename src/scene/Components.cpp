#include "scene/Components.h"

#include <iostream>

namespace engine::Component {

    // --- Transform ---
    Vec2 Transform::getPosition() const { return position; }
    void Transform::setPosition(const Vec2& pos) { position = pos; }
    void Transform::move(const Vec2& delta) { position += delta; }

    Vec2 Transform::getScale() const { return scale; }
    void Transform::setScale(const Vec2& s) { scale = s; }

    float Transform::getRotation() const { return rotation; }
    void Transform::setRotation(float r) { rotation = r; }
    void Transform::rotate(float r) {
        rotation += r;
        while (rotation >= 360) { rotation -= 360; }
        while (rotation < 0) { rotation += 360; }
    }

    // --- Single Sprite ---
    Texture* SingleSprite::getTexture() const { return texture; }
    void SingleSprite::setTexture(const char* path) {
        if (assets) {
            texture = assets->loadTexture(path);
        }
    }

    Vec2 SingleSprite::getDimensions() const { return dimensions; }
    void SingleSprite::setDimensions(const Vec2& d) { dimensions = d; }

    // --- Box Collider ---
    Vec2 BoxCollider::getDimensions() const { return dimensions; }
    void BoxCollider::setDimensions(const Vec2& d) {
        dimensions = d;
        half_x = d.x / 2.0f;
        half_y = d.y / 2.0f;
    }

    Vec2 BoxCollider::getMin() const { return transform->getPosition() - Vec2(half_x, half_y); }
    Vec2 BoxCollider::getMax() const { return transform->getPosition() + Vec2(half_x, half_y); }

}
