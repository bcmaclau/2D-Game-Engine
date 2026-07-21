#pragma once

#include "engine/math/Vector.h"
#include "engine/data_structures/PointerArrayList.h"

namespace engine {
    
    class BaseScene;
    class BaseUIObject;
    class AssetManager;

    namespace Component {
        enum class ID;
        class Transform;
        class Sprite;
        class BoxCollider;
    }

    namespace Collision {
        enum class Side;
    }

    namespace Component {
        enum class ID;
        class Transform;
        class Sprite;
        class BoxCollider;
    }

    class BaseGameObject {
        friend class BaseScene;
        friend class BaseUIObject;

    public:
        BaseGameObject() : scene_index(0), alive(true), screen_width_units(0), screen_height_units(0),
        assets(nullptr), to_instantiate(nullptr), ui_to_instantiate(nullptr),
        transform(nullptr), sprite(nullptr), box_collider(nullptr),
        tag(0) {}
        virtual ~BaseGameObject() {}

        void attachComponent(Component::ID component_id);
        
        template <typename T>
        T* instantiateGameObject() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, screen_width_units, screen_height_units, 0, to_instantiate, ui_to_instantiate);
            to_instantiate->push_back(obj);
            return obj;
        }
        void destroyGameObject(BaseGameObject* obj);
        void destroySelf();

        template <typename T>
        T* instantiateUIObject() {
            static_assert(std::is_base_of<BaseUIObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, screen_width_units, screen_height_units, 0, to_instantiate, ui_to_instantiate);
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
        Component::BoxCollider* box_collider;
        virtual void onCollision(BaseGameObject* other, Collision::Side side, float penetration) {}

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, float swu, float shu, unsigned int si, PointerArrayList<BaseGameObject>* ti, PointerArrayList<BaseUIObject>* uiti);
        void update(float dt);
        void fixedUpdate();
        void shutdown();

        unsigned int scene_index;
        bool alive;
        float screen_width_units, screen_height_units;
        AssetManager* assets;
        PointerArrayList<BaseGameObject>* to_instantiate;
        PointerArrayList<BaseUIObject>* ui_to_instantiate;

        int tag;
    };

}
