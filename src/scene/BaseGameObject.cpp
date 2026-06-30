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
            case Component::ID::SINGLE_SPRITE:
                if (single_sprite) { std::cout << "Game Object already has Single Sprite Component" << std::endl; return; }
                single_sprite = new Component::SingleSprite();
                single_sprite->assets = assets;
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

    void BaseGameObject::init(AssetManager* a, size_t si, std::vector<BaseGameObject*>* ti, std::vector<BaseGameObject*>* po) {
        assets = a;
        scene_index = si;
        to_instantiate = ti;
        physics_objects = po;

        attachComponent(Component::ID::TRANSFORM);

        onInit();

        if (box_collider) { physics_objects->push_back(this); }
    }

    void BaseGameObject::update(float dt) {
        onUpdate(dt);
    }

    void BaseGameObject::fixedUpdate() {
        onFixedUpdate();
    }

    void BaseGameObject::shutdown() {
        if (transform) { delete transform; }
        if (single_sprite) { delete single_sprite; }

        onShutdown();
    }

}
