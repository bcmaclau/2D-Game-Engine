#pragma once

#include "engine/scene/GameObject.h"
#include "engine/renderer/SpriteRenderer.h"
#include "engine/renderer/AssetManager.h"

#include <vector>

namespace engine {

    class Scene {
    public:
        Scene();
        ~Scene();

        void setAssets(AssetManager* a);

        GameObject* createDefaultGameObject();
        template <typename T = GameObject>
        T* instantiateGameObject() {
            static_assert(std::is_base_of<GameObject, T>::value, "T must derive from GameObject");

            T* obj = new T();
            obj->assets = assets;
            obj->onInit();
            obj->scene_index = objects.size();
            objects.push_back(obj);
            return obj;
        }
        void destroyGameObject(GameObject* obj);

        void update(float dt);
        void draw(SpriteRenderer* renderer);

        void clear();

        size_t getObjectCount();

    private:
        std::vector<GameObject*> objects;
        AssetManager* assets;
    };

}
