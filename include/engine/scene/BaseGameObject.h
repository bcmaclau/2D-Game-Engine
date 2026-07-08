#pragma once

#include <vector>

namespace engine {
    
    class BaseScene;
    class AssetManager;

    template <typename T>
    class PointerList;

    namespace Component {
        enum class ID;
        class Transform;
        class Sprite;
        class BoxCollider;
    }

    namespace Collision {
        enum class Side;
    }

    class BaseGameObject {
        friend class BaseScene;

    public:
        BaseGameObject() : alive(true), scene_index(0),
        transform(nullptr), sprite(nullptr), box_collider(nullptr),
        assets(nullptr), to_instantiate(nullptr), physics_objects(nullptr) {}
        virtual ~BaseGameObject() {}

        void attachComponent(Component::ID component_id);
        
        template <typename T>
        T* instantiateOther() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, 0, to_instantiate, physics_objects);
            to_instantiate->push_back(obj);
            return obj;
        }
        void destroySelf();
        void destroyOther(BaseGameObject* obj);

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
        void init(AssetManager* a, unsigned int si, PointerList<BaseGameObject>* ti, PointerList<BaseGameObject>* po);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        bool alive;
        unsigned int scene_index;
        AssetManager* assets;
        PointerList<BaseGameObject>* to_instantiate;
        PointerList<BaseGameObject>* physics_objects;
    
        int tag;
    };

}
