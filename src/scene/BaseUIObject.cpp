#include "scene/BaseUIObject.h"

namespace engine {
    
    void BaseUIObject::init(float swu, float shu, unsigned int si, PointerArrayList<BaseGameObject>* goti, PointerArrayList<BaseUIObject>* uiti) {
        screen_width_units = swu;
        screen_height_units = shu;
        scene_index = si;
        go_to_instantiate = goti;
        ui_to_instantiate = uiti;

        transform = new Component::Transform();
        sprite = new Component::Sprite();
        sprite->init(transform);

        onInit();
    }

    void BaseUIObject::destroyGameObject(BaseGameObject* obj) {
        obj->alive = false;
    }

    void BaseUIObject::destroyUIObject(BaseUIObject* ui_obj) {
        ui_obj->alive = false;
    }

    void BaseUIObject::destroySelf() {
        alive = false;
    }

    Vec2 BaseUIObject::getScreenDimensions() const {
        return Vec2(screen_width_units, screen_height_units);
    }

    void BaseUIObject::update(float dt) {
        onUpdate(dt);
    }

    void BaseUIObject::fixedUpdate() {
        onFixedUpdate();
    }

    void BaseUIObject::shutdown() {
        onShutdown();

        delete transform;
        sprite->shutdown();
        delete sprite;
    }

}
