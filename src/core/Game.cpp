#include "engine/core/Game.h"

#include <iostream>

namespace engine {

    Game::Game() {}
    Game::~Game() {}

    void Game::run() {
        init();

        while (running && !window.shouldClose()) {
            time.update();
            processInput();
            update(time.getDeltaTime());
            render();
        }

        shutdown();
    }

    void Game::init() {
        std::cout << "Initializing Game" << std::endl;

        window.init(800, 600, "test");

        onInit();
    }

    void Game::processInput() {
        window.pollEvents();
    }

    void Game::update(float dt) {
        std::cout << "Updating Game" << std::endl;

        onUpdate(dt);
    }

    void Game::render() {
        std::cout << "Rendering Game" << std::endl;

        onRender();

        window.swapBuffers();
    }

    void Game::shutdown() {
        std::cout << "Shutting Down Game" << std::endl;

        onShutdown();
    }

}
