#include "engine/scene/Scene.h"

namespace engine {

    Scene::Scene() {}
    Scene::~Scene() {}

    void Scene::setAssets(AssetManager* a) { assets = a; }

    GameObject* Scene::createDefaultGameObject() {
        GameObject* obj = new GameObject();
        obj->onInit();
        obj->scene_index = objects.size();
        objects.push_back(obj);
        return obj;
    }

    void Scene::destroyGameObject(GameObject* obj) {
        // O(1) game obj removal from the vector by swapping with the last obj then popping back
        size_t i = obj->scene_index;
        size_t back = objects.size() - 1;

        if (i != back) {
            std::swap(objects[i], objects[back]);
            objects[i]->scene_index = i;
        }
        objects.pop_back();
    }

    void Scene::update(float dt) {
        for (int i = 0; i < objects.size(); i++) {
            GameObject* obj = objects[i];
            if (obj->isActive()) { obj->onUpdate(dt); }
        }
    }

    void Scene::draw(SpriteRenderer* renderer) {
        for (int i = 0; i < objects.size(); i++) {
            GameObject* obj = objects[i];
            if (obj->active && obj->texture) {
                renderer->draw(obj->texture, obj->position, obj->size, obj->rotation);
            }
        }
    }

    void Scene::clear() {
        for (int i = 0; i < objects.size(); i++) {
            delete objects[i];
        }
        objects.clear();
    }

}
