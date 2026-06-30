#pragma once

#include "scene/BaseScene.h"
#include "renderer/AssetManager.h"
#include "physics/Collision.h"

#include <vector>

namespace engine {
    
    namespace Component {
        enum class ID;
        class Transform;
        class SingleSprite;
        class BoxCollider;
    }

    class BaseGameObject {
        friend class BaseScene;

    public:
        BaseGameObject() : alive(true), scene_index(0),
        transform(nullptr), single_sprite(nullptr), box_collider(nullptr),
        assets(nullptr), to_instantiate(nullptr), physics_objects(nullptr) {}
        virtual ~BaseGameObject() {}

        void attachComponent(Component::ID component_id);
        
        template <typename T>
        T* instantiateOther() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, 0, to_instantiate);
            to_instantiate->push_back(obj);
            return obj;
        }
        void destroySelf();
        void destroyOther(BaseGameObject* obj);

        // --- Components ---
        Component::Transform* transform;
        Component::SingleSprite* single_sprite;
        Component::BoxCollider* box_collider;
        virtual void onCollision(BaseGameObject* other, Collision::Side side, float penetration) {}

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, size_t si, std::vector<BaseGameObject*>* ti, std::vector<BaseGameObject*>* po);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        bool alive;
        size_t scene_index;
        AssetManager* assets;
        std::vector<BaseGameObject*>* to_instantiate;
        std::vector<BaseGameObject*>* physics_objects;
    };

}
