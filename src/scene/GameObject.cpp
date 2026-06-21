#include "engine/scene/GameObject.h"

#include <string>

namespace engine {

    GameObject::GameObject() : position({0.0f, 0.0f}), size({1.0f, 1.0f}), rotation(0.0f), texture(nullptr), active(true), scene_index(0) {}
    GameObject::~GameObject() {}

    void GameObject::onInit() {}
    void GameObject::onUpdate(float dt) {}

    void GameObject::setPosition(glm::vec2 pos) { position = pos; }
    glm::vec2 GameObject::getPosition() { return position; }
    void GameObject::move(glm::vec2 delta) { position += delta; }

    void GameObject::setSize(glm::vec2 s) { size = s; }
    glm::vec2 GameObject::getSize() { return size; }

    void GameObject::setRotation(float r) { rotation = r; }
    float GameObject::getRotation() { return rotation; }
    void GameObject::rotate(float r) { rotation += r; }

    void GameObject::setTexture(const char* path) {
        std::string path_s = path;
        texture = assets->loadTexture(path_s);
    }
    Texture* GameObject::getTexture() { return texture; }

    void GameObject::setActive(bool a) { active = a; }
    bool GameObject::isActive() { return active; }

    glm::vec2 GameObject::getMin() { return position - glm::vec2(size.x / 2.0f, size.y / 2.0f); }
    glm::vec2 GameObject::getMax() { return position + glm::vec2(size.x / 2.0f, size.y / 2.0f); }

}
