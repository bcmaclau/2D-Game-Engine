#pragma once

#include "engine/scene/GameObject.h"

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
        static bool AABBCollision(const GameObject& a, const GameObject& b);

        static CollisionResult AABBCollisionDetailed(const GameObject& a, const GameObject& b);

    private:
        Collision();
    };

}
