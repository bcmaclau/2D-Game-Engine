#pragma once

#include "scene/BaseGameObject.h"
#include "math/Vector.h"
#include "scene/component/Transform.h"

namespace engine::Component {

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
