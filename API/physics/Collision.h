#pragma once

#include "data_structures/PointerArrayList.h"

namespace engine {

    class BaseScene;
    class BaseGameObject;
    namespace Component { class Collider; } 

    struct AABB {
        float x_offset, y_offset;
        float half_width, half_height;
        float min_x, max_x;
        float min_y, max_y;
    };

    struct Point {
        float x_offset, y_offset;
        float x, y;
    };

    enum class CollisionSide {
        TOP, BOTTOM, LEFT, RIGHT
    };

    struct CollisionResult {
        BaseGameObject* other;
        CollisionSide side;
        float penetration;
    };

    class Collision {
    public:
        static void init(PointerArrayList<PointerArrayList<Component::Collider>>* cg, PointerArrayList<CollisionResult>* c);
        static void updateColliders();
        static void updateCollisions();
        static void endFrame();
        static void shutdown();

    private:
        Collision() {}

        static bool colliding(Component::Collider* a, Component::Collider* b);
        static bool AABBColliding(const AABB& a, const AABB& b);
        static bool AABBPointColliding(const AABB& a, const Point& b);
        static CollisionResult* createResult(Component::Collider* a, Component::Collider* b);
        static void resolveDynamicCollisions(Component::Collider* a, Component::Collider* b);

        static PointerArrayList<PointerArrayList<Component::Collider>>* collision_groups;
        static PointerArrayList<CollisionResult>* collisions;
    };

}
