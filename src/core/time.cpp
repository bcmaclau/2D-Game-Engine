#include "Time.h"

Time::Time() {
    
}

float Time::getDeltaTime() {
    float current_time = (float)glfwGetTime();
    float delta_time = current_time - last_time;
    last_time = current_time;
    return delta_time;
}