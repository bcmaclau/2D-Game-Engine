#include "engine/input/Input.h"

#include <GLFW/glfw3.h>

#include <cstring>

namespace engine {

    bool Input::current_keys[49] = {};
    bool Input::prev_keys[49] = {};

    void Input::init(GLFWwindow* window) {
        glfwSetKeyCallback(window, Input::keyCallback);

        for (int i = 0; i < 49; i++) {
            current_keys[i] = false;
            prev_keys[i] = false;
        }
    }

    bool Input::isKeyPushed(Key key) { return current_keys[(int)key] && !prev_keys[(int)key]; }

    bool Input::isKeyHeld(Key key) { return current_keys[(int)key]; }

    void Input::endFrame() {
        std::memcpy(prev_keys, current_keys, sizeof(current_keys));
    }

    void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Key k = fromGLFW(key);
        if (k == Key::UNKNOWN) { return; }
        if (action == GLFW_PRESS) { current_keys[(int)k] = true; }
        if (action == GLFW_RELEASE) { current_keys[(int)k] = false; }
    }

    Key Input::fromGLFW(int key) {
        switch (key) {
            case GLFW_KEY_SPACE: return Key::SPACE;
            case GLFW_KEY_ENTER: return Key::ENTER;
            case GLFW_KEY_ESCAPE: return Key::ESCAPE;
            case GLFW_KEY_TAB: return Key::TAB;
            case GLFW_KEY_BACKSPACE: return Key::BACKSPACE;
            case GLFW_KEY_UP: return Key::UP;
            case GLFW_KEY_DOWN: return Key::DOWN;
            case GLFW_KEY_LEFT: return Key::LEFT;
            case GLFW_KEY_RIGHT: return Key::RIGHT;
            case GLFW_KEY_A: return Key::A;
            case GLFW_KEY_B: return Key::B;
            case GLFW_KEY_C: return Key::C;
            case GLFW_KEY_D: return Key::D;
            case GLFW_KEY_E: return Key::E;
            case GLFW_KEY_F: return Key::F;
            case GLFW_KEY_G: return Key::G;
            case GLFW_KEY_H: return Key::H;
            case GLFW_KEY_I: return Key::I;
            case GLFW_KEY_J: return Key::J;
            case GLFW_KEY_K: return Key::K;
            case GLFW_KEY_L: return Key::L;
            case GLFW_KEY_M: return Key::M;
            case GLFW_KEY_N: return Key::N;
            case GLFW_KEY_O: return Key::O;
            case GLFW_KEY_P: return Key::P;
            case GLFW_KEY_Q: return Key::Q;
            case GLFW_KEY_R: return Key::R;
            case GLFW_KEY_S: return Key::S;
            case GLFW_KEY_T: return Key::T;
            case GLFW_KEY_U: return Key::U;
            case GLFW_KEY_V: return Key::V;
            case GLFW_KEY_W: return Key::W;
            case GLFW_KEY_X: return Key::X;
            case GLFW_KEY_Y: return Key::Y;
            case GLFW_KEY_Z: return Key::Z;
            case GLFW_KEY_1: return Key::NUM_1;
            case GLFW_KEY_2: return Key::NUM_2;
            case GLFW_KEY_3: return Key::NUM_3;
            case GLFW_KEY_4: return Key::NUM_4;
            case GLFW_KEY_5: return Key::NUM_5;
            case GLFW_KEY_6: return Key::NUM_6;
            case GLFW_KEY_7: return Key::NUM_7;
            case GLFW_KEY_8: return Key::NUM_8;
            case GLFW_KEY_9: return Key::NUM_9;
            case GLFW_KEY_0: return Key::NUM_0;
            case GLFW_KEY_LEFT_SHIFT: return Key::LEFT_SHIFT;
            case GLFW_KEY_RIGHT_SHIFT: return Key::RIGHT_SHIFT;
            case GLFW_KEY_LEFT_CONTROL: return Key::LEFT_CONTROL;
            case GLFW_KEY_RIGHT_CONTROL: return Key::RIGHT_CONTROL;
            default: return Key::UNKNOWN;
        }
    }

}
