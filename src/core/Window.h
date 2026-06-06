#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
public:
    Window();

    bool shouldClose();
    void swapBuffers();

private:
    static bool init_b;
    int init();

    GLFWwindow* window;

};