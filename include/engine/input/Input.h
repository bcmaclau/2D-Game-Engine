#pragma once

#include "KeyCode.h"

struct GLFWwindow;

namespace engine {
    
    class Input {
    public:
        static void init(GLFWwindow* window);
        static bool isKeyPushed(Key key);
        static bool isKeyHeld(Key key);

        static void endFrame();
    
    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static Key fromGLFW(int key);

        static bool current_keys[49];
        static bool prev_keys[49];
    };

}
