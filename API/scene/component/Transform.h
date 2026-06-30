#pragma once

#include "math/Vector.h"

namespace engine::Component {

    class Transform {
    public:
        Transform() : position({ 0.0f, 0.0f }), scale({1.0f, 1.0f}), rotation(0.0f) {}
        ~Transform() {}

        Vec2 getPosition() const;
        void setPosition(const Vec2& pos);
        void move(const Vec2& delta);

        Vec2 getScale() const;
        void setScale(const Vec2& s);

        float getRotation() const;
        void setRotation(float r);
        void rotate(float r);

    private:
        Vec2 position;
        Vec2 scale;
        float rotation;
    };

}
