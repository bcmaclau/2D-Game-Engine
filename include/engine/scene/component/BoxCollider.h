#pragma once

#include "engine/math/Vector.h"

namespace engine {

    class BaseGameObject;

}

namespace engine::Component {

    class Transform;

    class BoxCollider {
        friend class engine::BaseGameObject;

    public:
        BoxCollider() : dimensions(Vec2(1.0f, 1.0f)) {}
        ~BoxCollider() {}

        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);

        Vec2 getMin() const;
        Vec2 getMax() const;

    private:
        Transform* transform;
        Vec2 dimensions;
        float half_x, half_y;
    };

}
