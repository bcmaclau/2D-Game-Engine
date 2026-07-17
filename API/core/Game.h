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
        screen_width(800), screen_height(600), screen_units_v(10.0f) {}
        virtual ~Game() {}

        void run(BaseScene& first_scene);

        void setTitle(const char* t);
        void setNumWorldUnitsVert(float n);
        void setWindowDimensions(unsigned int w, unsigned int h);

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onRender() {}
        virtual void onShutdown() {}

    private:
        char title[64] = { '\0' };
        void init(BaseScene& first_scene);

        bool running;

        float update_interval, acc;
        void update(float dt);

        void render();

        void shutdown();

        BaseScene* active_scene;
        bool first_scene;
        void loadNewScene();

        float screen_units_v;
        unsigned int screen_width, screen_height;
        Window* window;
        Time* time;
        AssetManager* assets;
    };

}
