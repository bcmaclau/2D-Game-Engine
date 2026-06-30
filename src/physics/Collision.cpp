#include "physics/Collision.h"

#include "scene/BaseScene.h"
#include "scene/BaseGameObject.h"
#include "scene/component/Components.h"

#include <iostream>

std::vector<engine::BaseGameObject*>* engine::Collision::physics_objects = nullptr;
std::vector<engine::Collision::Result*>* engine::Collision::collisions = nullptr;

namespace engine {

    void Collision::init(std::vector<BaseGameObject*>* po, std::vector<Result*>* c) {
        physics_objects = po;
        collisions = c;
    }

    void Collision::updateCollisions() {
        // currently only implements the narrow phase for every game object
        // TODO: make broad phase

        BaseGameObject* a, * b;
        for (int i = 0; i < (int)physics_objects->size() - 1; i++) {
            for (int j = i + 1; j < (int)physics_objects->size(); j++) {
                a = physics_objects->at(i);
                b = physics_objects->at(j);

                // Collision Detected
                if (colliding(a, b)) {
                    Result* result = new Result();
                    result->a = a;
                    result->b = b;

                    float top_pen = a->box_collider->getMax().y - b->box_collider->getMin().y;
                    float bottom_pen = b->box_collider->getMax().y - a->box_collider->getMin().y;
                    float left_pen = b->box_collider->getMax().x - a->box_collider->getMin().x;
                    float right_pen = a->box_collider->getMax().x - b->box_collider->getMin().x;

                    // make sure all penetration values are positive
                    if (top_pen < 0) { top_pen *= -1; }
                    if (bottom_pen < 0) { bottom_pen *= -1; }
                    if (left_pen < 0) { left_pen *= -1; }
                    if (right_pen < 0) { right_pen *= -1; }

                    // find the smallest penetration
                    result->penetration = top_pen;
                    result->side = Side::TOP;
                    if (bottom_pen < result->penetration) {
                        result->penetration = bottom_pen;
                        result->side = Side::BOTTOM;
                    }
                    if (left_pen < result->penetration) {
                        result->penetration = left_pen;
                        result->side = Side::LEFT;
                    }
                    if (right_pen < result->penetration) {
                        result->penetration = right_pen;
                        result->side = Side::RIGHT;
                    }

                    collisions->push_back(result);
                }
            }
        }
    }

    bool Collision::colliding(BaseGameObject* a, BaseGameObject* b) {
        Vec2 aMin = a->box_collider->getMin(), aMax = a->box_collider->getMax();
        Vec2 bMin = b->box_collider->getMin(), bMax = b->box_collider->getMax();
        return aMin.x < bMax.x && aMax.x > bMin.x && aMin.y < bMax.y && aMax.y > bMin.y;
    }

    void Collision::endFrame() {
        for (int i = 0; i < collisions->size(); i++) {
            delete collisions->at(i);
        }
        collisions->clear();
    }

    void Collision::shutdown() {
        physics_objects = nullptr;
        collisions = nullptr;
    }

}
