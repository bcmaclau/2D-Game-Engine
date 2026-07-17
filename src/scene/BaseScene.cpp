#include "scene/BaseScene.h"

#include "scene/BaseGameObject.h"
#include "scene/component/Components.h"
#include "physics/Collision.h"

#include <iostream>

namespace engine {

    void BaseScene::endGame() { end_game = true; }

    void BaseScene::destroy(BaseGameObject* obj) {
        // remove from all PointerLists
        removeFromGO(obj, game_objects);
        if (obj->sprite) {
            switch (obj->sprite->render_layer) {
                case Component::Sprite::RenderLayer::ENVIRONMENT:
                    removeFromRL(obj, environment_layer);
                    break;
                case Component::Sprite::RenderLayer::ENTITY:
                    removeFromRL(obj, entity_layer);
                    break;
                case Component::Sprite::RenderLayer::UI:
                    removeFromRL(obj, ui_layer);
                    break;
                default:
                    removeFromRL(obj, background_layer);
                    break;
            }
        }
        if (obj->box_collider) {
            removeFromPO(obj, physics_objects);
        }

        // delete all components
        delete obj->transform;
        if (obj->sprite) { obj->sprite->shutdown(); delete obj->sprite; }
        if (obj->box_collider) { delete obj->box_collider; }

        obj->shutdown();
        delete obj;
    }

    Vec2 BaseScene::getScreenDimensions() const { return Vec2((float)screen_width, (float)screen_height); }

    void BaseScene::init(AssetManager* a, unsigned int sw, unsigned int sh, float suv) {
        std::cout << "Scene SUV: " << suv << std::endl;

        assets = a;
        screen_width = sw;
        screen_height = sh;
        sprite_renderer = new SpriteRenderer();
        sprite_renderer->init();
        camera = new Camera2D();
        camera->init(sw, sh, suv);
        game_objects = new PointerList<BaseGameObject>();
        to_instantiate = new PointerList<BaseGameObject>();
        background_layer = new PointerList<BaseGameObject>();
        environment_layer = new PointerList<BaseGameObject>();
        entity_layer = new PointerList<BaseGameObject>();
        ui_layer = new PointerList<BaseGameObject>();        
        physics_objects = new PointerList<BaseGameObject>();
        collisions = new PointerList<Collision::Result>();
        Collision::init(physics_objects, collisions);

        onInit();
    }

    void BaseScene::update(float dt) {
        handlePhysics();

        onUpdate(dt);

        BaseGameObject* obj = nullptr;
        for (int i = 0; i < game_objects->size(); i++) {
            obj = (*game_objects)[i];
            if (obj->alive) { obj->update(dt); }
        }
    }

    void BaseScene::handlePhysics() {
        // handle collisions
        Collision::updateCollisions();
        Collision::Result* result = nullptr;
        for (int i = 0; i < collisions->size(); i++) {
            result = (*collisions)[i];
            
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
        for (int i = 0; i < game_objects->size(); i++) {
            obj = (*game_objects)[i];
            if (obj->alive) { obj->fixedUpdate(); }
        }
    }

    void BaseScene::draw() {
        sprite_renderer->beginFrame(camera);

        // render order: background -> environment -> entity -> ui
        BaseGameObject* obj = nullptr;
        for (int i = 0; i < background_layer->size(); i++) {
            obj = (*background_layer)[i];
            sprite_renderer->drawSprite(obj->sprite, obj->transform);
        }
        for (int i = 0; i < environment_layer->size(); i++) {
            obj = (*environment_layer)[i];
            sprite_renderer->drawSprite(obj->sprite, obj->transform);
        }
        for (int i = 0; i < entity_layer->size(); i++) {
            obj = (*entity_layer)[i];
            sprite_renderer->drawSprite(obj->sprite, obj->transform);
        }
        for (int i = 0; i < ui_layer->size(); i++) {
            obj = (*ui_layer)[i];
            sprite_renderer->drawUI(obj->sprite, obj->transform);
        }
    }

    void BaseScene::endFrame() {
        // instantiate new game objects from the current frame
        // this needs to happen before destruction because of scene indices
        // render order and collision groups get sorted here
        BaseGameObject* obj = nullptr;
        for (int i = 0; i < to_instantiate->size(); i++) {
            obj = (*to_instantiate)[i];
            obj->scene_index = game_objects->size();
            game_objects->push_back(obj);

            // render order sorting
            if (obj->sprite) {
                switch (obj->sprite->render_layer) {
                    case Component::Sprite::RenderLayer::ENVIRONMENT:
                        obj->sprite->layer_index = environment_layer->size();
                        environment_layer->push_back(obj);
                        break;
                    case Component::Sprite::RenderLayer::ENTITY:
                        obj->sprite->layer_index = entity_layer->size();
                        entity_layer->push_back(obj);
                        break;
                    case Component::Sprite::RenderLayer::UI:
                        obj->sprite->layer_index = ui_layer->size();
                        ui_layer->push_back(obj);
                        break;
                    default:
                        obj->sprite->layer_index = background_layer->size();
                        background_layer->push_back(obj);
                        break;
                }
            }

            // TODO: collision grouping
            // for now all physics objects exist in one list
            if (obj->box_collider) {
                obj->box_collider->phys_index = physics_objects->size();
                physics_objects->push_back(obj);
            }
        }
        to_instantiate->clear();

        // destroy any game objects that need it this frame
        PointerList<BaseGameObject> to_destroy;
        for (int i = 0; i < game_objects->size(); i++) {
            obj = (*game_objects)[i];
            if (!obj->alive) { to_destroy.push_back(obj); }
        }
        for (int i = 0; i < to_destroy.size(); i++) { destroy(to_destroy[i]); }

        Collision::endFrame();

        sprite_renderer->endFrame();
    }

    void BaseScene::shutdown() {
        onShutdown();

        BaseGameObject* obj = nullptr;
        for (int i = 0; i < game_objects->size(); i++) {
            obj = (*game_objects)[i];
            obj->shutdown();
            delete obj;
        }
        game_objects->clear();
        physics_objects->clear();

        sprite_renderer->shutdown();
        delete sprite_renderer;
        delete camera;
        delete game_objects;
        delete to_instantiate;
        delete physics_objects;
        delete collisions;
        Collision::shutdown();
    }

    void BaseScene::removeFromGO(BaseGameObject* obj, PointerList<BaseGameObject>* list) {
        unsigned int obj_index = obj->scene_index;
        unsigned int last_index = list->size() - 1;

        if (obj_index != last_index) {
            list->swap_indices(obj_index, last_index);
            (*list)[obj_index]->scene_index = obj_index;
        }

        list->pop_back();
    }
    void BaseScene::removeFromRL(BaseGameObject* obj, PointerList<BaseGameObject>* list) {
        unsigned int obj_index = obj->sprite->layer_index;
        unsigned int last_index = list->size() - 1;

        if (obj_index != last_index) {
            list->swap_indices(obj_index, last_index);
            (*list)[obj_index]->sprite->layer_index = obj_index;
        }

        list->pop_back();
    }
    void BaseScene::removeFromPO(BaseGameObject* obj, PointerList<BaseGameObject>* list) {
        unsigned int obj_index = obj->box_collider->phys_index;
        unsigned int last_index = list->size() - 1;

        if (obj_index != last_index) {
            list->swap_indices(obj_index, last_index);
            (*list)[obj_index]->box_collider->phys_index = obj_index;
        }

        list->pop_back();
    }

}
