#pragma once

#include "scene/BaseScene.h"
#include "renderer/AssetManager.h"
#include "physics/Collision.h"
#include "container/PointerList.h"

namespace engine {
    
    namespace Component {
        enum class ID;
        class Transform;
        class Sprite;
        class BoxCollider;
    }

    class BaseGameObject {
        friend class BaseScene;

    public:
        BaseGameObject() : alive(true), scene_index(0),
        transform(nullptr), sprite(nullptr), box_collider(nullptr),
        assets(nullptr), to_instantiate(nullptr) {}
        virtual ~BaseGameObject() {}

        void attachComponent(Component::ID component_id);
        
        template <typename T>
        T* instantiateOther() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, screen_width, screen_height, 0, to_instantiate);
            to_instantiate->push_back(obj);
            return obj;
        }
        void destroySelf();
        void destroyOther(BaseGameObject* obj);

        Vec2 getScreenDimensions() const;

        // tag
        void setTag(int t);
        int getTag() const;

        // --- Components ---
        Component::Transform* transform;
        Component::Sprite* sprite;
        Component::BoxCollider* box_collider;
        virtual void onCollision(BaseGameObject* other, Collision::Side side, float penetration) {}

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, unsigned int sw, unsigned int sh, unsigned int si, PointerList<BaseGameObject>* ti);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        unsigned int screen_width, screen_height;
        bool alive;
        unsigned int scene_index;
        AssetManager* assets;
        PointerList<BaseGameObject>* to_instantiate;

        int tag;
    };

}
