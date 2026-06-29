#include "core/Time.h"

#include <GLFW/glfw3.h>

namespace engine {

    void Time::update() {
        float ct = (float)glfwGetTime();
        dt = ct - lt;
        lt = ct;
    }

    float Time::getDeltaTime() {
        return dt;
    }

}
