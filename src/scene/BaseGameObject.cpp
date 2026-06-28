#include "engine/scene/BaseGameObject.h"

#include "engine/scene/Components.h"

#include <iostream>

namespace engine {

    void BaseGameObject::attachComponent(component::ID component_id) {
        switch (component_id) {
            case component::ID::TRANSFORM:
                if (transform) { std::cout << "Game Object Already Has Transform Component" << std::endl; return; }
                transform = new component::Transform();
                return;
            case component::ID::SINGLE_SPRITE:
                if (single_sprite) { std::cout << "Game Object already has Single Sprite Component" << std::endl; return; }
                single_sprite = new component::SingleSprite();
                single_sprite->assets = assets;
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

    void BaseGameObject::init(AssetManager* a, size_t si, std::vector<BaseGameObject*>* ti) {
        assets = a;
        scene_index = si;
        to_instantiate = ti;

        attachComponent(component::ID::TRANSFORM);

        onInit();
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
