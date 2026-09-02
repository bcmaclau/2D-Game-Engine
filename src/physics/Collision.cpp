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
                    resolveDynamicCollisions(a, b);
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
                            resolveDynamicCollisions(collider_a, collider_b);
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

    void Collision::resolveDynamicCollisions(Component::Collider* a, Component::Collider* b) {
        if (a->type != Component::Collider::Type::DYNAMIC && b->type != Component::Collider::Type::DYNAMIC) { return; }
        if (a->type == Component::Collider::Type::TRIGGER || b->type == Component::Collider::Type::TRIGGER) { return; }
        if (a->type == Component::Collider::Type::STATIC && b->type == Component::Collider::Type::STATIC) { return; }

        Component::Collider* d1 = nullptr, * d2 = nullptr, * s1 = nullptr;
        if (a->type == Component::Collider::Type::DYNAMIC) { d1 = a; }
        else { s1 = a; }
        if (b->type == Component::Collider::Type::DYNAMIC) {
            if (d1) { d2 = b; }
            else { d1 = b; }
        }
        else { s1 = b; }

        // both colliders are dynamic
        if (d1 && d2) {
            Component::Collider* r1 = nullptr, * r2 = nullptr, * n1 = nullptr, * n2 = nullptr;
            /*
            if (d1->react_physics) { r1 = d1; }
            else { n1 = d1; }
            if (d2->react_physics) {
                if (r1) { r2 = d2; }
                else { r1 = d2; } 
            }
            else {
                if (n1) { n2 = d2; }
                else { n1 = d2; }
            }
            */

            n1 = d1;
            n2 = d2;

            // both colliders are non-reactive
            //if (n1 && n2) {
            if (true) {
                if (n1->transform->getPosition() == n1->last_pos) {
                    CollisionResult* result = createResult(n2, n1);
                    if (result->side == CollisionSide::TOP) {
                        n2->transform->move(Vec2(0.0f, -result->penetration));
                    }
                    else if (result->side == CollisionSide::BOTTOM) {
                        n2->transform->move(Vec2(0.0f, result->penetration));
                    }
                    else if (result->side == CollisionSide::LEFT) {
                        n2->transform->move(Vec2(result->penetration, 0.0f));
                    }
                    else {
                        n2->transform->move(Vec2(-result->penetration, 0.0f));
                    }
                    delete result;
                }
                else if (n2->transform->getPosition() == n2->last_pos) {
                    CollisionResult* result = createResult(n1, n2);
                    if (result->side == CollisionSide::TOP) {
                        n1->transform->move(Vec2(0.0f, -result->penetration));
                    }
                    else if (result->side == CollisionSide::BOTTOM) {
                        n1->transform->move(Vec2(0.0f, result->penetration));
                    }
                    else if (result->side == CollisionSide::LEFT) {
                        n1->transform->move(Vec2(result->penetration, 0.0f));
                    }
                    else {
                        n1->transform->move(Vec2(-result->penetration, 0.0f));
                    }
                    delete result;
                }
                else {
                    CollisionResult* result = createResult(n1, n2);
                    
                    float n1_ratio = 0.0f;
                    float n2_ratio = 0.0f;
                    if (result->side == CollisionSide::TOP || result->side == CollisionSide::BOTTOM) {
                        float n1_part = std::abs(n1->last_pos.y - n1->transform->getPosition().y);
                        float n2_part = std::abs(n2->last_pos.y - n2->transform->getPosition().y);
                        n1_ratio = n1_part / (n1_part + n2_part);
                        n2_ratio = n2_part / (n1_part + n2_part);
                    }
                    else {
                        float n1_part = std::abs(n1->last_pos.x - n1->transform->getPosition().x);
                        float n2_part = std::abs(n2->last_pos.x - n2->transform->getPosition().x);
                        n1_ratio = n1_part / (n1_part + n2_part);
                        n2_ratio = n2_part / (n1_part + n2_part);
                    }

                    if (result->side == CollisionSide::TOP) {
                        n1->transform->move(Vec2(0.0f, -n1_ratio * result->penetration));
                        n2->transform->move(Vec2(0.0f, n2_ratio * result->penetration));
                    }
                    else if (result->side == CollisionSide::BOTTOM) {
                        n1->transform->move(Vec2(0.0f, n1_ratio * result->penetration));
                        n2->transform->move(Vec2(0.0f, -n2_ratio * result->penetration));
                    }
                    else if (result->side == CollisionSide::LEFT) {
                        n1->transform->move(Vec2(n1_ratio * result->penetration, 0.0f));
                        n2->transform->move(Vec2(-n2_ratio * result->penetration, 0.0f));
                    }
                    else {
                        n1->transform->move(Vec2(-n1_ratio * result->penetration, 0.0f));
                        n2->transform->move(Vec2(n2_ratio * result->penetration, 0.0f));
                    }
                    delete result;
                }
            }
        }
        // 1 dynamic collider, 1 static
        else {
            CollisionResult* result = createResult(d1, s1);
            if (result->side == CollisionSide::TOP) {
                d1->transform->move(Vec2(0.0f, -result->penetration));
            }
            else if (result->side == CollisionSide::BOTTOM) {
                d1->transform->move(Vec2(0.0f, result->penetration));
            }
            else if (result->side == CollisionSide::LEFT) {
                d1->transform->move(Vec2(result->penetration, 0.0f));
            }
            else {
                d1->transform->move(Vec2(-result->penetration, 0.0f));
            }
            delete result;
        }
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
