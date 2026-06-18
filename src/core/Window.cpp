#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/core/Window.h"

#include <iostream>

namespace engine {

    Window::Window() {}
    Window::~Window() {}

    bool Window::init(int width, int height, const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glViewport(0, 0, width, height);

        return true;
    }

    void Window::shutdown() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
    }

    int Window::getWidth() {
        return width;
    }

    int Window::getHeight() {
        return height;
    }

    GLFWwindow* Window::getNativeHandle() {
        return window;
    }

}
