#pragma once

#include "scene/BaseScene.h"
#include "scene/BaseUIObject.h"
#include "physics/Collision.h"
#include "data_structures/PointerArrayList.h"

namespace engine {

    namespace Component {
        enum class ID;
        class Transform;
        class Sprite;
        class Collider;
    }

    class BaseGameObject {
        friend class BaseScene;
        friend class BaseUIObject;

    public:
        BaseGameObject() : scene_index(0), alive(true), screen_width_units(0), screen_height_units(0),
        go_to_instantiate(nullptr), ui_to_instantiate(nullptr),
        transform(nullptr), sprite(nullptr), collider(nullptr), ungrouped_colliders(nullptr),
        tag(0) {}
        virtual ~BaseGameObject() {}

        void attachComponent(Component::ID component_id);

        template <typename T>
        T* instantiateGameObject() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(screen_width_units, screen_height_units, 0, go_to_instantiate, ui_to_instantiate, ungrouped_colliders);
            go_to_instantiate->push_back(obj);
            return obj;
        }
        void destroyGameObject(BaseGameObject* obj);
        void destroySelf();

        template <typename T>
        T* instantiateUIObject() {
            static_assert(std::is_base_of<BaseUIObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(screen_width_units, screen_height_units, 0, go_to_instantiate, ui_to_instantiate);
            ui_to_instantiate->push_back(obj);
            return obj;
        }
        void destroyUIObject(BaseUIObject* obj);

        Vec2 getScreenDimensions() const;

        // tag
        void setTag(int t);
        int getTag() const;

        // --- Components ---
        Component::Transform* transform;
        Component::Sprite* sprite;
        Component::Collider* collider;

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

        // --- Physics Methods ---
        virtual void onCollisionEnter(CollisionResult* collision) {}
        virtual void onCollisionHold(CollisionResult* collision) {}
        virtual void onCollisionExit(BaseGameObject* other) {}

    private:
        void init(float swu, float shu, unsigned int si, PointerArrayList<BaseGameObject>* goti, PointerArrayList<BaseUIObject>* uiti, PointerArrayList<Component::Collider>* uc);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        unsigned int scene_index;
        bool alive;
        float screen_width_units, screen_height_units;

        PointerArrayList<BaseGameObject>* go_to_instantiate;
        PointerArrayList<BaseUIObject>* ui_to_instantiate;

        PointerArrayList<Component::Collider>* ungrouped_colliders;

        int tag;
    };

}
