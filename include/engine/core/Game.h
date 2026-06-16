#pragma once

#include "engine/core/Window.h"
#include "engine/core/Time.h"

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

    private:
        void init();
        void processInput();
        void update(float dt);
        void render();
        void shutdown();

        bool running = true;
    };

}
