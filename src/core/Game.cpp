#include <glad/glad.h>

#include "engine/core/Game.h"

namespace engine {

    Game::Game() {}
    Game::~Game() {}

    void Game::run() {
        init();

        float acc = 0.0f;
        float update_interval = 1.0f / 60.0f;

        while (running && !window.shouldClose()) {
            time.update();
            acc += time.getDeltaTime();

            while (acc >= update_interval) {
                processInput();

                update(time.getDeltaTime());
                acc -= update_interval;

                Input::endFrame();
            }

            render();
        }

        shutdown();
    }

    void Game::init() {
        window.init(800, 600, "test");

        camera.init(800, 600);

        sprite_renderer.init();

        Input::init(window.getNativeHandle());

        onInit();
    }

    void Game::processInput() {
        window.pollEvents();
    }

    void Game::update(float dt) {
        onUpdate(dt);
    }

    void Game::render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite_renderer.beginFrame(&camera);
        onRender();
        sprite_renderer.endFrame();

        window.swapBuffers();
    }

    void Game::shutdown() {
        sprite_renderer.shutdown();
        onShutdown();
        window.shutdown();
    }

}
