#pragma once

#include "engine/math/Vector.h"

struct GLFWwindow;

namespace engine {
    
    class Input {
        friend class Game;
        
    public:
        enum class Key {
            UNKNOWN = -1,
            SPACE, ENTER, ESCAPE, TAB, BACKSPACE,
            UP, DOWN, LEFT, RIGHT,
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0,
            LEFT_SHIFT, RIGHT_SHIFT, LEFT_CONTROL, RIGHT_CONTROL
        };

        enum class Button {
            UNKNOWN = -1,
            LEFT, RIGHT, MIDDLE
        };

        static bool isKeyPushed(Key key);
        static bool isKeyHeld(Key key);
        
        static Vec2 getMousePos();
        static bool isMousePushed(Button button);
        static bool isMouseHeld(Button button);

    private:
        Input() {}
        
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        
        static Key fromGLFW(int key);
        
        static bool current_keys[49];
        static bool prev_keys[49];
        
        static void init(GLFWwindow* window);
        static void endFrame();
    };

}
