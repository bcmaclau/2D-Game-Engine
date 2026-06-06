#pragma once

#include "Window.h"
#include "Time.h"

class Game {

public:
    Game();

    void run();

private:
    Window window;
    Time time;

    enum GAME_ERROR {
        WINDOW_INIT_ERROR
    };
    int game_error;

};