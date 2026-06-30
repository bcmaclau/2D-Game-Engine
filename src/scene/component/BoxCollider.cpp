#include "scene/component/BoxCollider.h"

#include "math/Vector.h"

namespace engine::Component {

    Vec2 BoxCollider::getDimensions() const { return dimensions; }
    void BoxCollider::setDimensions(const Vec2& d) {
        dimensions = d;
        half_x = d.x / 2.0f;
        half_y = d.y / 2.0f;
    }

    Vec2 BoxCollider::getMin() const { return transform->getPosition() - Vec2(half_x, half_y); }
    Vec2 BoxCollider::getMax() const { return transform->getPosition() + Vec2(half_x, half_y); }

}
