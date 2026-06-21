#pragma once

#include "engine/core/Window.h"
#include "engine/core/Time.h"

#include "engine/renderer/Texture.h"
#include "engine/renderer/SpriteRenderer.h"
#include "engine/renderer/AssetManager.h"

#include "engine/input/Input.h"

#include "engine/scene/Scene.h"

namespace engine {

    class Game {
    public:
        Game();
        virtual ~Game();

        void run();

    protected:
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onRender() {}
        virtual void onShutdown() {}

        Window window;
        Time time;

        AssetManager assets;
        Scene scene;
        Camera2D camera;
        SpriteRenderer sprite_renderer;

    private:
        void init();
        void processInput();
        void update(float dt);
        void render();
        void shutdown();

        bool running = true;
    };

}
