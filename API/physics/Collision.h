#pragma once

#include "scene/BaseGameObject.h"

namespace engine {

    enum class CollisionSide {
        NONE, TOP, BOTTOM, LEFT, RIGHT
    };

    struct CollisionResult {
        bool collided = false;
        CollisionSide side = CollisionSide::NONE;
        float penetration = 0.0f;
    };

    class Collision {
    public:
        static bool AABBCollision(const BaseGameObject& a, const BaseGameObject& b);

        static CollisionResult AABBCollisionDetailed(const BaseGameObject& a, const BaseGameObject& b);

    private:
        Collision() {}
    };

}
