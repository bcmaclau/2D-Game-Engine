#include "scene/BaseScene.h"

#include "scene/BaseGameObject.h"
#include "scene/Components.h"
#include "physics/Collision.h"

#include <iostream>

namespace engine {

    void BaseScene::endGame() { end_game = true; }

    void BaseScene::destroy(BaseGameObject* obj) {
        size_t i = obj->scene_index;
        size_t last_i = game_objects.size() - 1;
        if (!(i <= last_i && i >= 0)) {
            std::cout << "Invalid scene index" << std::endl;
            return;
        }

        if (i != last_i) {
            std::swap(game_objects[i], game_objects[last_i]);
            game_objects[i]->scene_index = i;
        }

        game_objects[last_i]->shutdown();
        delete game_objects[last_i];
        game_objects.pop_back();
    }

    void BaseScene::init(AssetManager* a, int screen_width, int screen_height) {
        assets = a;
        sprite_renderer = new SpriteRenderer();
        sprite_renderer->init();
        camera = new Camera2D();
        camera->init(screen_width, screen_height);
        Collision::init(&physics_objects, &collisions);
        onInit();
    }

    void BaseScene::update(float dt) {
        handlePhysics();

        onUpdate(dt);

        BaseGameObject* obj = nullptr;
        for (int i = 0; i < game_objects.size(); i++) {
            obj = game_objects[i];
            if (obj->alive) { obj->update(dt); }
        }
    }

    void BaseScene::handlePhysics() {
        // handle collisions
        Collision::updateCollisions();
        Collision::Result* result = nullptr;
        for (int i = 0; i < collisions.size(); i++) {
            result = collisions[i];
            
            Collision::Side opposite_side;
            switch (result->side) {
                case Collision::Side::TOP:
                    opposite_side = Collision::Side::BOTTOM;
                    break;
                case Collision::Side::BOTTOM:
                    opposite_side = Collision::Side::TOP;
                    break;
                case Collision::Side::LEFT:
                    opposite_side = Collision::Side::RIGHT;
                    break;
                default:
                    opposite_side = Collision::Side::LEFT;
                    break;
            }
            
            result->a->onCollision(result->b, result->side, result->penetration);
            result->b->onCollision(result->a, opposite_side, result->penetration);
        }
    }

    void BaseScene::fixedUpdate() {
        onFixedUpdate();

        BaseGameObject* obj = nullptr;
        for (int i = 0; i < game_objects.size(); i++) {
            obj = game_objects[i];
            if (obj->alive) { obj->fixedUpdate(); }
        }
    }

    void BaseScene::draw() {
        sprite_renderer->beginFrame(camera);

        BaseGameObject* obj = nullptr;
        Component::SingleSprite* sprite = nullptr;
        for (int i = 0; i < game_objects.size(); i++) {
            obj = game_objects[i];
            sprite = obj->single_sprite;
            glm::vec2 pos = glm::vec2(obj->transform->getPosition().x, obj->transform->getPosition().y);
            glm::vec2 dim = glm::vec2(sprite->getDimensions().x, sprite->getDimensions().y);
            if (sprite) {
                sprite_renderer->draw(sprite->getTexture(), pos, dim, obj->transform->getRotation());
            }
        }
    }

    void BaseScene::endFrame() {
        // instantiate new game objects from the current frame
        // this needs to happen before destruction because of scene indices
        BaseGameObject* obj = nullptr;
        for (int i = 0; i < to_instantiate.size(); i++) {
            obj = to_instantiate[i];
            obj->scene_index = game_objects.size();
            game_objects.push_back(obj);
        }
        to_instantiate.clear();

        // destroy any game objects that need it this frame
        std::vector<BaseGameObject*> to_destroy;
        for (int i = 0; i < game_objects.size(); i++) {
            obj = game_objects[i];
            if (!obj->alive) { to_destroy.push_back(obj); }
        }
        for (int i = 0; i < to_destroy.size(); i++) { destroy(to_destroy[i]); }

        Collision::endFrame();

        sprite_renderer->endFrame();
    } 

    void BaseScene::shutdown() {
        onShutdown();

        BaseGameObject* obj = nullptr;
        for (int i = 0; i < game_objects.size(); i++) {
            obj = game_objects[i];
            obj->shutdown();
            delete obj;
        }
        game_objects.clear();
        physics_objects.clear();

        sprite_renderer->shutdown();
        delete sprite_renderer;
        delete camera;
        Collision::shutdown();
    }

}
