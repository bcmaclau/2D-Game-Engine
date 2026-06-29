#include "core/Game.h"

#include "input/Input.h"

#include <iostream>

namespace engine {

    void Game::run(BaseScene& first_scene) {
        init(first_scene);

        // main game loop
        while (running && !window->shouldClose() && !active_scene->end_game) {
            // simple pipeline: 
            // get time -> get user input -> update game -> render game
            time->update();
            window->pollEvents();
            update(time->getDeltaTime());
            render();

            if (active_scene->swap_scene) {
                loadNewScene();
                //Input::reset_keys();
            }

            active_scene->endFrame();
            Input::endFrame();
        }

        shutdown();
    }

    void Game::init(BaseScene& first_scene) {
        // window initialization
        window = new Window();
        if (!window->init(screen_width, screen_height, "testing")) {
            std::cout << "Failed to create GLFW window. Shutting Down" << std::endl;
            running = false;
        }

        // input initialization
        Input::init(window->getNativeHandle());

        // scene initialization
        assets = new AssetManager();
        active_scene = &first_scene;
        active_scene->init(assets, screen_width, screen_height);

        time = new Time();

        // user-implemented game init
        onInit();
    }

    void Game::update(float dt) {
        // update runs every time this function is called immediately
        onUpdate(dt);
        active_scene->update(dt);
        
        // fixed update always runs at a rate of 60 times per second
        acc += dt;
        while (acc >= update_interval) {
            onFixedUpdate();
            active_scene->fixedUpdate();
            acc -= update_interval;
        }
    }

    void Game::render() {
        // render pipline:
        // clear window -> draw to screen -> swap buffers
        window->clear();

        onRender();
        active_scene->draw();

        window->swapBuffers();
    }

    void Game::shutdown() {
        // shutdown order:
        // game objects, textures, shaders, then window last
        onShutdown();
        assets->clear();
        delete assets;
        window->shutdown();
        delete window;
        delete time;
    }

    void Game::loadNewScene() {
        active_scene->shutdown();
        if (!first_scene) { delete active_scene; }
        else { first_scene = false; }
        active_scene = active_scene->new_scene;
        active_scene->init(assets, screen_width, screen_height);
    }

}
