#pragma once

#include "engine/scene/component/Transform.h"
#include "engine/data_structures/PointerArrayList.h"

namespace engine {
    class BaseScene;
    class BaseGameObject;
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
    class Collision;
    struct CollisionResult;
}

namespace engine::Component {

    class Collider {
        friend class engine::BaseScene;
        friend class engine::BaseGameObject;
        friend class engine::Collision;

    public:
        enum class Type {
            DYNAMIC,
            STATIC,
            TRIGGER
        };

        Collider() : go_reference(nullptr), transform(nullptr), type(Type::STATIC), set_type(false),
        collision_group(nullptr), group_index(0), active(true),
        aabbs(nullptr), points(nullptr), current_aabb(nullptr), current_point(nullptr), prev_collisions(nullptr), current_collisions(nullptr),
        velocity(Vec2(0.0f, 0.0f)), acceleration(Vec2(0.0f, 0.0f)), mass(1.0f) {}
        ~Collider() {}

        void setType(Type t);

        void addBoxCollider(const Vec2& offset, const Vec2& dimensions);
        void addPointCollider(const Vec2& offset);

        // functions that affect dynamic colliders
        void addForce(const Vec2& force);
        void setVelocity(const Vec2& v);

    private:
        void init(BaseGameObject* gor, Transform* t, PointerArrayList<Collider>* cg);
        void shutdown();

        void update();

        // info for engine systems
        BaseGameObject* go_reference;
        Transform* transform;
        bool set_type;
        Type type;
        PointerArrayList<Collider>* collision_group;
        unsigned int group_index;
        bool active;

        // info relevant for collision detection
        PointerArrayList<AABB>* aabbs;
        PointerArrayList<Point>* points;
        AABB* current_aabb;
        Point* current_point;
        PointerArrayList<BaseGameObject>* prev_collisions;
        PointerArrayList<CollisionResult>* current_collisions;

        // info relevant if collider is dynamic
        Vec2 velocity, acceleration;
        float mass;
    };

}
