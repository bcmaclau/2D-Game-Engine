#include "engine/physics/Collision.h"

#include <algorithm>
#include <cmath>

namespace engine {

    bool Collision::AABBCollision(const BaseGameObject& a, const BaseGameObject& b) {
        /*
        glm::vec2 aMin = a.getMin(), aMax = a.getMax();
        glm::vec2 bMin = b.getMin(), bMax = b.getMax();

        return aMin.x < bMax.x && aMax.x > bMin.x && aMin.y < bMax.y && aMax.y > bMin.y;
        */
        return false;
    }

    CollisionResult Collision::AABBCollisionDetailed(const BaseGameObject& a, const BaseGameObject& b) {
        /*
        CollisionResult result;

        if (!AABBCollision(a, b)) { return result; }
        result.collided = true;

        glm::vec2 aMin = a.getMin(), aMax = a.getMax();
        glm::vec2 bMin = b.getMin(), bMax = b.getMax();

        float right = std::abs(aMax.x - bMin.x);
        float left = std::abs(aMin.x - bMax.x);
        float top = std::abs(aMax.y - bMin.y);
        float bottom = std::abs(aMin.y - bMax.y);

        float min_overlap = std::min({ right, left, top, bottom });

        if (min_overlap == right) { result.side = CollisionSide::RIGHT; }
        else if (min_overlap == left) { result.side = CollisionSide::LEFT; }
        else if (min_overlap == top) { result.side = CollisionSide::TOP; }
        else { result.side = CollisionSide::BOTTOM; }

        result.penetration = min_overlap;

        return result;
        */
        CollisionResult result;
        return result;        
    }

}
