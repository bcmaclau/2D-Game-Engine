#include "core/Game.h"

#include "input/Input.h"

#include <iostream>
#include <cstring>

namespace engine {

    void Game::run(BaseScene& first_scene) {
        init(first_scene);

        // main game loop
        while (running && !window->shouldClose() && !active_scene->end_game) {
            // simple pipeline: 
            // get time -> get user input -> update game -> render game
            window->pollEvents();
            time->update();
            update(time->getDeltaTime());
            render();
            
            if (active_scene->swap_scene) {
                loadNewScene();
            }
            
            Input::endFrame();
            active_scene->endFrame();
        }
        
        shutdown();
    }

    void Game::setTitle(const char* t) {
        if (strlen(t) > 64) { std::cout << "Title must be no longer than 64 characters" << std::endl; }

        memset(title, '\0', 64);
        memcpy(title, t, strlen(t));
    }

    void Game::setNumWorldUnitsVert(float n) {
        screen_units_v = n;
    }

    void Game::setWindowDimensions(unsigned int w, unsigned int h) {
        screen_width = w;
        screen_height = h;
    }

    void Game::init(BaseScene& first_scene) {
        // window initialization
        window = new Window();
        if (!window->init(screen_width, screen_height, title)) {
            std::cout << "Failed to create GLFW window. Shutting Down" << std::endl;
            running = false;
        }

        // input initialization
        Input::init(window->getNativeHandle(), screen_height);

        // scene initialization
        active_scene = &first_scene;
        active_scene->init(screen_width, screen_height, screen_units_v);

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
        window->shutdown();
        delete window;
        delete time;
    }

    void Game::loadNewScene() {
        active_scene->shutdown();
        if (!first_scene) { delete active_scene; }
        else { first_scene = false; }
        active_scene = active_scene->new_scene;
        active_scene->init(screen_width, screen_height, screen_units_v);
    }

}
