#pragma once

struct GLFWwindow;

namespace engine {

    class Window {
    public:
        Window() : width(0), height(0) {}
        ~Window() {}

        bool init(unsigned int width, unsigned int height, const char* title);
        void shutdown();

        bool shouldClose();
        void pollEvents();

        void clear();
        void swapBuffers();

        int getWidth() const;
        int getHeight() const;
        GLFWwindow* getNativeHandle() const;

    private:
        GLFWwindow* window;
        unsigned int width;
        unsigned int height;
    };

}