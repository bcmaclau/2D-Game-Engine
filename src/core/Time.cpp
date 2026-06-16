#include "engine/core/Time.h"

#include <GLFW/glfw3.h>

namespace engine {

    Time::Time() : dt(0.0f), lt(0.0f) {}
    Time::~Time() {}

    void Time::update() {
        float ct = (float)glfwGetTime();
        dt = ct - lt;
        lt = ct;
    }

    float Time::getDeltaTime() {
        return dt;
    }

}
