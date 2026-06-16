#pragma once

struct GLFWwindow;

namespace engine {

    class Window {
    public:
        Window();
        ~Window();

        bool init(int width, int height, const char* title);
        void shutdown();

        bool shouldClose();
        void pollEvents();
        void swapBuffers();

        int getWidth();
        int getHeight();
        GLFWwindow* getNativeHandle();

    private:
        GLFWwindow* window;
        int width = 0;
        int height = 0;
    };

}