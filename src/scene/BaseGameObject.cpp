#include "scene/BaseGameObject.h"

#include "scene/component/Components.h"

#include <iostream>

namespace engine {

    void BaseGameObject::attachComponent(Component::ID component_id) {
        switch (component_id) {
            case Component::ID::TRANSFORM:
                if (transform) { std::cout << "Game Object Already Has Transform Component" << std::endl; return; }
                transform = new Component::Transform();
                return;
            case Component::ID::SPRITE:
                if (sprite) { std::cout << "Game Object already has Single Sprite Component" << std::endl; return; }
                sprite = new Component::Sprite();
                sprite->init(assets);
                return;
            case Component::ID::BOX_COLLIDER:
                if (box_collider) { std::cout << "Game Object already has Box Collider Component" << std::endl; return; }
                box_collider = new Component::BoxCollider();
                box_collider->transform = transform;
                box_collider->phys_id = physics_objects->size();
                physics_objects->push_back(this);
                return;
            default:
                std::cout << "Invalid Component ID" << std::endl;
                return;
        }
    }

    void BaseGameObject::destroySelf() {
        alive = false;
    }

    void BaseGameObject::destroyOther(BaseGameObject* obj) {
        obj->alive = false;
    }

    void BaseGameObject::setTag(int t) { tag = t; }
    int BaseGameObject::getTag() const { return tag; }

    void BaseGameObject::init(AssetManager* a, unsigned int si, PointerList<BaseGameObject>* ti, PointerList<BaseGameObject>* po) {
        assets = a;
        scene_index = si;
        to_instantiate = ti;
        physics_objects = po;

        attachComponent(Component::ID::TRANSFORM);

        onInit();
    }

    void BaseGameObject::update(float dt) {
        onUpdate(dt);
    }

    void BaseGameObject::fixedUpdate() {
        // update sprite animations on a fixed interval
        if (sprite->active_sprite->interval > 0) {
            sprite->active_sprite->interval_acc++;
            if (sprite->active_sprite->interval_acc == sprite->active_sprite->interval) {
                sprite->active_sprite->interval_acc = 0;
                sprite->active_sprite->current_frame++;
                if (sprite->active_sprite->current_frame >= 1.0f / sprite->active_sprite->frame_width) { sprite->active_sprite->current_frame = 0; }
            }
        }

        onFixedUpdate();
    }

    void BaseGameObject::shutdown() {
        if (transform) { delete transform; }
        if (sprite) { sprite->shutdown(); delete sprite; }
        if (box_collider) {
            // same O(1) removal from physics_objects as scene's game_objects
            unsigned int last = physics_objects->size() - 1, current = box_collider->phys_id;
            if (current != last) {
                (*physics_objects)[last]->box_collider->phys_id = current;
                physics_objects->swap_indices(current, last);
            }
            physics_objects->pop_back();
            delete box_collider;
        }

        onShutdown();
    }

}
