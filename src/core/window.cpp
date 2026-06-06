#include "Window.h"

bool Window::init_b = false;

Window::Window() {
    // if init returns not 0, set window to null
    int val = 0;
    if (!init_b) {
        val = init();
    }
    if (val) {
        window = NULL;
        return;
    }

    init_b = true;
}

// basic initialization of GLFW and GLAD
int Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "2D Game Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, 800, 600);

    return 0;
}

// return whether the window should close
bool Window::shouldClose() {
    if (window == NULL) {
        return true;
    }

    return glfwWindowShouldClose(window);
}

// swaps window buffers and polls glfw events; currently clears the screen
void Window::swapBuffers() {
    if (window == NULL) {
        return;
    }

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}