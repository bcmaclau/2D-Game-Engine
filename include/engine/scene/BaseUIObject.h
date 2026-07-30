#pragma once

#include "engine/scene/component/Components.h"
#include "engine/input/Input.h"

namespace engine {

    class BaseUIObject {
        friend class BaseScene;
        friend class BaseGameObject;

    public:
        BaseUIObject() : scene_index(0), alive(true),
        go_to_instantiate(nullptr), ui_to_instantiate(nullptr),
        tag(0),
        current_hovering(false), prev_hovering(false) {}
        virtual ~BaseUIObject() {}

        template <typename T>
        T* instantiateGameObject() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(screen_width_units, screen_height_units, 0, go_to_instantiate, ui_to_instantiate);
            go_to_instantiate->push_back(obj);
            return obj;
        }
        void destroyGameObject(BaseGameObject* obj);
        
        template <typename T>
        T* instantiateUIObject() {
            static_assert(std::is_base_of<BaseUIObject, T>::value, "T must derive from BaseUIObject");

            T* ui_obj = new T();
            ui_obj->init(screen_width_units, screen_height_units, 0, go_to_instantiate, ui_to_instantiate);
            ui_to_instantiate->push_back(ui_obj);
            return ui_obj;
        }
        void destroyUIObject(BaseUIObject* ui_obj);
        void destroySelf();

        Vec2 getScreenDimensions() const;

        Component::Transform* transform;
        Component::Sprite* sprite;

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

        virtual void onClickEnter(Input::Button button) {}
        virtual void onClickHold(Input::Button button) {}
        virtual void onClickExit(Input::Button button) {}

        virtual void onHoverEnter() {}
        virtual void onHoverHold() {}
        virtual void onHoverExit() {}

    private:
        void init(float swu, float shu, unsigned int si, PointerArrayList<BaseGameObject>* goti, PointerArrayList<BaseUIObject>* uiti);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        unsigned int scene_index;
        bool alive;
        float screen_width_units, screen_height_units;

        PointerArrayList<BaseGameObject>* go_to_instantiate;
        PointerArrayList<BaseUIObject>* ui_to_instantiate;

        int tag;

        bool current_hovering, prev_hovering;
    };

}
