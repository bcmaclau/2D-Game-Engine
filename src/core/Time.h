#pragma once

#include <GLFW/glfw3.h>

class Time {
public:
    Time();

    float getDeltaTime();

private:
    float last_time = 0;

};