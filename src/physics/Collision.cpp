#include "physics/Collision.h"

#include "scene/BaseScene.h"
#include "scene/BaseGameObject.h"
#include "scene/component/Collider.h"

#include <cmath>

engine::PointerArrayList<engine::PointerArrayList<engine::Component::Collider>>* engine::Collision::collision_groups = nullptr;
engine::PointerArrayList<engine::CollisionResult>* engine::Collision::collisions = nullptr;

namespace engine {

    void Collision::init(PointerArrayList<PointerArrayList<Component::Collider>>* cg, PointerArrayList<CollisionResult>* c) {
        collision_groups = cg;
        collisions = c;
    }

    void Collision::updateColliders() {
        for (unsigned int i = 0; i < collision_groups->size(); i++) {
            PointerArrayList<Component::Collider>* group = (*collision_groups)[i];
            for (unsigned int j = 0; j < group->size(); j++) {
                Component::Collider* collider = (*group)[j];
                collider->update();
            }
        }
    }

    void Collision::updateCollisions() {
        // finds collision between 2 ungrouped colliders
        PointerArrayList<Component::Collider>* ungrouped_colliders = (*collision_groups)[0];
        for (unsigned int i = 0; i < ungrouped_colliders->size(); i++) {
            Component::Collider* a = (*ungrouped_colliders)[i];
            for (unsigned int j = i + 1; j < ungrouped_colliders->size(); j++) {
                Component::Collider* b = (*ungrouped_colliders)[j];
                if (colliding(a, b)) {
                    CollisionResult* a_result = createResult(a, b);
                    CollisionResult* b_result = createResult(b, a);
                    a->current_collisions->push_back(a_result);
                    b->current_collisions->push_back(b_result);
                }
            }
        }


        // finding collisions between different groups
        for (unsigned int i = 0; i < collision_groups->size(); i++) {
            PointerArrayList<Component::Collider>* group_a = (*collision_groups)[i];
            for (unsigned int j = i + 1; j < collision_groups->size(); j++) {
                PointerArrayList<Component::Collider>* group_b = (*collision_groups)[j];

                for (unsigned int k = 0; k < group_a->size(); k++) {
                    Component::Collider* collider_a = (*group_a)[k];
                    for (unsigned int l = 0; l < group_b->size(); l++) {
                        Component::Collider* collider_b = (*group_b)[l];
                        if (colliding(collider_a, collider_b)) {
                            CollisionResult* a_result = createResult(collider_a, collider_b);
                            CollisionResult* b_result = createResult(collider_b, collider_a);
                            collider_a->current_collisions->push_back(a_result);
                            collider_b->current_collisions->push_back(b_result);
                        }
                    }
                }
            }
        }
    }

    bool Collision::colliding(Component::Collider* a, Component::Collider* b) {
        for (unsigned int i = 0; i < a->aabbs->size(); i++) {
            AABB* a_aabb = (*a->aabbs)[i];

            for (unsigned int j = 0; j < b->aabbs->size(); j++) {
                AABB* b_aabb = (*b->aabbs)[j];
                if (AABBColliding(*a_aabb, *b_aabb)) {
                    a->current_aabb = a_aabb;
                    a->current_point = nullptr;
                    b->current_aabb = b_aabb;
                    b->current_point = nullptr;
                    return true;
                }
            }

            for (unsigned int j = 0; j < b->points->size(); j++) {
                Point* b_point = (*b->points)[j];
                if (AABBPointColliding(*a_aabb, *b_point)) {
                    a->current_aabb = a_aabb;
                    a->current_point = nullptr;
                    b->current_aabb = nullptr;
                    b->current_point = b_point;
                    return true;
                }
            }
        }

        for (unsigned int i = 0; i < a->points->size(); i++) {
            Point* a_point = (*a->points)[i];
            for (unsigned int j = 0; j < b->aabbs->size(); j++) {
                AABB* b_aabb = (*b->aabbs)[j];
                if (AABBPointColliding(*b_aabb, *a_point)) {
                    a->current_aabb = nullptr;
                    a->current_point = a_point;
                    b->current_aabb = b_aabb;
                    b->current_point = nullptr;
                    return true;
                }
            }
        }
        return false;
    }

    bool Collision::AABBColliding(const AABB& a, const AABB& b) {
        return a.max_x >= b.min_x && a.min_x <= b.max_x && a.max_y >= b.min_y && a.min_y <= b.max_y;
    }

    bool Collision::AABBPointColliding(const AABB& a, const Point& b) {
        return a.min_x <= b.x && a.max_x >= b.x && a.min_y <= b.y && a.max_y >= b.y;
    }

    CollisionResult* Collision::createResult(Component::Collider* a, Component::Collider* b) {
        CollisionResult* ret = new CollisionResult();
        ret->other = b->go_reference;

        // find the shortest penetration
        float pen = 0.0f;
        CollisionSide side = CollisionSide::TOP;
        if (a->current_aabb && b->current_aabb) {
            float top = std::abs(a->current_aabb->max_y - b->current_aabb->min_y);
            float bottom = std::abs(a->current_aabb->min_y - b->current_aabb->max_y);
            float right = std::abs(a->current_aabb->max_x - b->current_aabb->min_x);
            float left = std::abs(a->current_aabb->min_x - b->current_aabb->max_x);
            pen = top;
            if (bottom < pen) { pen = bottom; side = CollisionSide::BOTTOM; }
            if (right < pen) { pen = right; side = CollisionSide::RIGHT; }
            if (left < pen) { pen = left; side = CollisionSide::LEFT; }
        }
        else if (a->current_aabb && b->current_point) {}

        ret->penetration = pen;
        ret->side = side;
        return ret;
    }

    void Collision::endFrame() {
        for (int i = 0; i < collisions->size(); i++) {
            delete collisions->at(i);
        }
        collisions->clear();
    }

    void Collision::shutdown() {
        collision_groups = nullptr;
        collisions = nullptr;
    }

}
