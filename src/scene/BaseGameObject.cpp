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
                sprite->init(transform);
                return;
            case Component::ID::BOX_COLLIDER:
                if (box_collider) { std::cout << "Game Object already has Box Collider Component" << std::endl; return; }
                box_collider = new Component::BoxCollider();
                box_collider->init(transform);
                return;
            default:
                std::cout << "Invalid Component ID" << std::endl;
                return;
        }
    }

    void BaseGameObject::destroySelf() {
        alive = false;
    }

    void BaseGameObject::destroyGameObject(BaseGameObject* obj) {
        obj->alive = false;
    }

    void BaseGameObject::destroyUIObject(BaseUIObject* obj) {
        obj->alive = false;
    }

    Vec2 BaseGameObject::getScreenDimensions() const { return Vec2(screen_width_units, screen_height_units); }

    void BaseGameObject::setTag(int t) { tag = t; }
    int BaseGameObject::getTag() const { return tag; }

    void BaseGameObject::init(float swu, float shu, unsigned int si, PointerArrayList<BaseGameObject>* goti, PointerArrayList<BaseUIObject>* uiti) {
        screen_width_units = swu;
        screen_height_units = shu;
        scene_index = si;
        go_to_instantiate = goti;
        ui_to_instantiate = uiti;

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
        onShutdown();

        // delete components
        delete transform;
        if (sprite) { sprite->shutdown(); delete sprite; }
        if (box_collider) { delete box_collider; }
    }

}
