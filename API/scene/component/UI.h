#pragma once

#include "math/Vector.h"
#include "scene/component/Transform.h"

namespace engine::Component {

    class UI {
    public:
        UI() {}
        ~UI() {}

        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);
    
    private:
        Transform* transform;
        Vec2 dimensions;
        float half_x, halfy;
    };

}
