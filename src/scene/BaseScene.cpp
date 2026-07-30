#include "scene/BaseScene.h"

#include "scene/BaseGameObject.h"
#include "scene/component/Components.h"
#include "physics/Collision.h"
#include "input/UIInteraction.h"
#include "input/Input.h"

#include <iostream>

namespace engine {

    void BaseScene::endGame() { end_game = true; }

    void BaseScene::destroyGameObject(BaseGameObject* obj) {
        obj->alive = false;
    }

    void BaseScene::destroyUIObject(BaseUIObject* obj) {
        obj->alive = false;
    }

    Vec2 BaseScene::getScreenDimensions() const { return Vec2(screen_width_units, screen_height_units); }

    Vec2 BaseScene::getCameraPosition() const { return Vec2(camera->getPosition().x, camera->getPosition().y); }
    void BaseScene::setCameraPosition(const Vec2& pos) { camera->setPosition({ pos.x, pos.y }); }
    void BaseScene::moveCamera(const Vec2& delta) { camera->setPosition({ camera->getPosition().x + delta.x, camera->getPosition().y + delta.y }); }
    void BaseScene::cameraFollow(BaseGameObject* obj) { camera_follow = obj; }
    void BaseScene::cameraUnfollow() { camera_follow = nullptr; }

    void BaseScene::init(unsigned int sw, unsigned int sh, float suv) {
        screen_width_pixels = sw;
        screen_height_pixels = sh;
        screen_width_units = suv * ((float)sw / (float)sh);
        screen_height_units = suv;
        
        camera = new Camera2D();
        camera->init(sw, sh, suv);
        Input::initCamera(camera);
        game_objects = new PointerArrayList<BaseGameObject>();
        go_to_instantiate = new PointerArrayList<BaseGameObject>();
        ui_objects = new PointerArrayList<BaseUIObject>();  
        ui_to_instantiate = new PointerArrayList<BaseUIObject>();
        go_render_order = new PointerLinkedList<Component::Sprite>();
        ui_render_order = new PointerLinkedList<Component::Sprite>();
        physics_objects = new PointerArrayList<BaseGameObject>();
        collisions = new PointerArrayList<Collision::Result>();
        Collision::init(physics_objects, collisions);

        useSprites();
        in_use_sprites = false;
        AssetManager::loadSprites();
        BatchRenderer::init(AssetManager::texture_array_id, AssetManager::max_tex_width, AssetManager::max_tex_height);

        onInit();
    }

    void BaseScene::addSpriteDirectory(const char* path, bool recurse) {
        if (in_use_sprites) { AssetManager::addSpriteDirectory(path, recurse); }
        else { std::cerr << "Attempting to load sprites after loading phase" << std::endl; }
    }

    void BaseScene::update(float dt) {
        handlePhysics();
        handleUI();

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

    void BaseScene::handleUI() {
        BaseUIObject* ui_obj = nullptr;
        for (int i = 0; i < ui_objects->size(); i++) {
            ui_obj = (*ui_objects)[i];

            ui_obj->prev_hovering = ui_obj->current_hovering;
            ui_obj->current_hovering = UIInteraction::isHovering(ui_obj->transform, ui_obj->sprite);
            if (!ui_obj->prev_hovering && ui_obj->current_hovering) { ui_obj->onHoverEnter(); }
            if (ui_obj->current_hovering) { ui_obj->onHoverHold(); }
            if (ui_obj->prev_hovering && !ui_obj->current_hovering) { ui_obj->onHoverExit(); }

            if (ui_obj->current_hovering) {
                for (int i = 0; i < 3; i++) {
                    Input::Button button = (Input::Button)i;
                    if (Input::isMousePushed(button)) { ui_obj->onClickEnter(button); }
                    if (Input::isMouseHeld(button)) { ui_obj->onClickHold(button); }
                    if (Input::isMouseReleased(button)) { ui_obj->onClickExit(button); }
                }
            }
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

    // prepares the renderer and passes all sprite components and their transforms
    void BaseScene::draw() {
        if (camera_follow) { setCameraPosition(camera_follow->transform->getPosition()); }
        BatchRenderer::startBatch(camera);
        BatchRenderer::drawInOrder(go_render_order, ui_render_order);
    }

    // incorporates and removes game objects that were instantiated or destroyed this frame
    // also calls the end frame function for every system initialized by the scene
    void BaseScene::endFrame() {
        // instantiate new game objects from the current frame
        BaseGameObject* obj = nullptr;
        for (int i = 0; i < go_to_instantiate->size(); i++) {
            obj = (*go_to_instantiate)[i];
            obj->scene_index = game_objects->size();
            game_objects->push_back(obj);

            // inserting the sprite to the render order and storing the node for O(1) removal
            if (obj->sprite) {
                obj->sprite->order_node = insertSpriteToRO(obj->sprite, go_render_order);
            }

            // TODO: collision grouping
            // for now all physics objects exist in one list
            if (obj->box_collider) {
                obj->box_collider->phys_index = physics_objects->size();
                physics_objects->push_back(obj);
            }
        }
        go_to_instantiate->clear();

        // instantiate ui objects
        BaseUIObject* ui_obj = nullptr;
        for (int i = 0; i < ui_to_instantiate->size(); i++) {
            ui_obj = (*ui_to_instantiate)[i];
            ui_obj->scene_index = ui_objects->size();
            ui_objects->push_back(ui_obj);

            ui_obj->sprite->order_node = insertSpriteToRO(ui_obj->sprite, ui_render_order);
        }
        ui_to_instantiate->clear();

        // destroy any game objects that need it this frame
        PointerArrayList<BaseGameObject> go_to_destroy;
        for (int i = 0; i < game_objects->size(); i++) {
            obj = (*game_objects)[i];
            if (!obj->alive) { go_to_destroy.push_back(obj); }
        }
        for (int i = 0; i < go_to_destroy.size(); i++) {
            obj = go_to_destroy[i];
            if (obj == camera_follow) { cameraUnfollow(); }
            removeGOFromLists(obj);
            if (obj->sprite) { go_render_order->remove(obj->sprite->order_node); }
            obj->shutdown();
            delete obj;
        }

        // destroy any ui objects that need it this frame
        PointerArrayList<BaseUIObject> ui_to_destroy;
        for (int i = 0; i < ui_objects->size(); i++) {
            ui_obj = (*ui_objects)[i];
            if (!ui_obj->alive) { ui_to_destroy.push_back(ui_obj); }
        }
        for (int i = 0; i < ui_to_destroy.size(); i++) {
            ui_obj = ui_to_destroy[i];
            removeUIFromList(ui_obj);
            ui_render_order->remove(ui_obj->sprite->order_node);
            ui_obj->shutdown();
            delete ui_obj;
        }

        Collision::endFrame();
    }

    // shuts down every system initialized by the scene
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

        BaseUIObject* ui_obj = nullptr;
        for (int i = 0; i < ui_objects->size(); i++) {
            ui_obj = (*ui_objects)[i];
            ui_obj->shutdown();
            delete ui_obj;
        }
        ui_objects->clear();

        AssetManager::reset();
        BatchRenderer::shutdown();

        delete camera;
        delete game_objects;
        delete physics_objects;
        delete ui_objects;
        delete go_to_instantiate;
        delete ui_to_instantiate;
        delete go_render_order;
        delete ui_render_order;
        delete collisions;
        Collision::shutdown();
    }

    // removes a gameobject from the game objects pointer list and physics list
    void BaseScene::removeGOFromLists(BaseGameObject* obj) {
        unsigned int obj_index = obj->scene_index;
        unsigned int last_index = game_objects->size() - 1;

        if (obj_index != last_index) {
            game_objects->swap_indices(obj_index, last_index);
            (*game_objects)[obj_index]->scene_index = obj_index;
        }

        game_objects->pop_back();

        if (obj->box_collider) {
            obj_index = obj->box_collider->phys_index;
            last_index = physics_objects->size() - 1;

            if (obj_index != last_index) {
                physics_objects->swap_indices(obj_index, last_index);
                (*physics_objects)[obj_index]->box_collider->phys_index = obj_index;
            }

            physics_objects->pop_back();
        }
    }
    
    // removes a ui object from the ui objects pointer list
    void BaseScene::removeUIFromList(BaseUIObject* obj) {
        unsigned int obj_index = obj->scene_index;
        unsigned int last_index = ui_objects->size() - 1;

        if (obj_index == last_index) {
            ui_objects->swap_indices(obj_index, last_index);
            (*ui_objects)[obj_index]->scene_index = obj_index;
        }

        ui_objects->pop_back();
    }

    // inserts and removes sprites from the rendering order
    PLLNode<Component::Sprite>* BaseScene::insertSpriteToRO(Component::Sprite* sprite, PointerLinkedList<Component::Sprite>* render_order) {
        if (render_order->size() == 0) { return render_order->push_back(sprite); }

        float order = sprite->getRenderLayer();
        if (order >= render_order->getTail()->getData()->getRenderLayer()) { return render_order->push_back(sprite); }

        PLLNode<Component::Sprite>* current = render_order->getHead();
        while (current->getNext() && current->getData()->getRenderLayer() < order) { current = current->getNext(); }
        return render_order->insert_before(current, sprite);
    }

}
