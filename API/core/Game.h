#pragma once

#include "core/Window.h"
#include "core/Time.h"
#include "renderer/AssetManager.h"
#include "scene/BaseScene.h"

namespace engine {

    class Game {
    public:    
        Game() : running(true),
        update_interval(1.0f / 60.0f), acc(0.0f),
        active_scene(nullptr), first_scene(true),
        screen_width(800), screen_height(600) {}
        virtual ~Game() {}

        void run(BaseScene& first_scene);

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onRender() {}
        virtual void onShutdown() {}

    private:
        void init(BaseScene& first_scene);

        bool running;

        float update_interval, acc;
        void update(float dt);

        void render();

        void shutdown();

        BaseScene* active_scene;
        bool first_scene;
        void loadNewScene();

        int screen_width, screen_height;
        Window* window;
        Time* time;
        AssetManager* assets;
    };

}
