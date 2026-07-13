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

    Vec2 BaseGameObject::getScreenDimensions() const { return Vec2((float)screen_width, (float)screen_height); }

    void BaseGameObject::setTag(int t) { tag = t; }
    int BaseGameObject::getTag() const { return tag; }

    void BaseGameObject::init(AssetManager* a, unsigned int sw, unsigned int sh, unsigned int si, PointerList<BaseGameObject>* ti) {
        assets = a;
        screen_width = sw;
        screen_height = sh;
        scene_index = si;
        to_instantiate = ti;

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
    }

}
