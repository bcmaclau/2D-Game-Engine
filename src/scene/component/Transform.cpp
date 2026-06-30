#include "scene/component/Transform.h"

namespace engine::Component {

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

}
