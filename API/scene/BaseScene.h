#pragma once

#include "renderer/AssetManager.h"
#include "renderer/SpriteRenderer.h"
#include "renderer/Camera2D.h"

#include <vector>

namespace engine {

    class BaseGameObject;

    class BaseScene {
        friend class Game;

    public:
        BaseScene() : swap_scene(false), new_scene(nullptr), end_game(false) {}
        virtual ~BaseScene() = default;

        template <typename T>
        void swapScene() {
            static_assert(std::is_base_of<BaseScene, T>::value, "T must derive from BaseScene");

            new_scene = new T();
            swap_scene = true;
        }

        void endGame();

        template <typename T>
        T* instantiate() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, game_objects.size(), &to_instantiate);
            game_objects.push_back(obj);
            return obj;
        }
        void destroy(BaseGameObject* obj);

    protected:
        // user implemented functions
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, int screen_width, int screen_height);
        void update(float dt);
        void fixedUpdate();
        void draw();
        void endFrame();
        void shutdown();

        void dynamicInstantiate(BaseGameObject* obj);

        bool swap_scene;
        BaseScene* new_scene;
        bool end_game;

        AssetManager* assets;
        SpriteRenderer* sprite_renderer;
        Camera2D* camera;

        std::vector<BaseGameObject*> game_objects;
        std::vector<BaseGameObject*> to_instantiate;
    };

}
