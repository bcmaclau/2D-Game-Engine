#include "Game.h"

Game::Game() {
    // checking for initialization errors

    // if the window should close before running the main loop there was an error initializing it
    if (window.shouldClose()) {
        game_error = WINDOW_INIT_ERROR;
    }
}

void Game::run() {
    // main game loop, exits when the window closes or game detects an error
    while (!window.shouldClose() && !game_error) {
        
        // simple code to test delta time and print FPS
        float delta_time = time.getDeltaTime();
        std::cout << "Current FPS: " << 1 / delta_time << std::endl;

        // testing the 
        window.swapBuffers();
    }

    // if the game detected an error, print the error code
    if (game_error) {
        std::cout << "Game Error: " << game_error << std::endl;
    }
}