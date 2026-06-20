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

    bool Input::isKeyPushed(Key key) { return current_keys[key] && !prev_keys[key]; }

    bool Input::isKeyHeld(Key key) { return current_keys[key]; }

    void Input::endFrame() {
        std::memcpy(prev_keys, current_keys, sizeof(current_keys));
    }

    void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Key k = fromGLFW(key);
        if (k == UNKNOWN) { return; }
        if (action == GLFW_PRESS) { current_keys[k] = true; }
        if (action == GLFW_RELEASE) { current_keys[k] = false; }
    }

    Key Input::fromGLFW(int key) {
        switch (key) {
            case GLFW_KEY_SPACE: return SPACE;
            case GLFW_KEY_ENTER: return ENTER;
            case GLFW_KEY_ESCAPE: return ESCAPE;
            case GLFW_KEY_TAB: return TAB;
            case GLFW_KEY_BACKSPACE: return BACKSPACE;
            case GLFW_KEY_UP: return UP;
            case GLFW_KEY_DOWN: return DOWN;
            case GLFW_KEY_LEFT: return LEFT;
            case GLFW_KEY_RIGHT: return RIGHT;
            case GLFW_KEY_A: return A;
            case GLFW_KEY_B: return B;
            case GLFW_KEY_C: return C;
            case GLFW_KEY_D: return D;
            case GLFW_KEY_E: return E;
            case GLFW_KEY_F: return F;
            case GLFW_KEY_G: return G;
            case GLFW_KEY_H: return H;
            case GLFW_KEY_I: return I;
            case GLFW_KEY_J: return J;
            case GLFW_KEY_K: return K;
            case GLFW_KEY_L: return L;
            case GLFW_KEY_M: return M;
            case GLFW_KEY_N: return N;
            case GLFW_KEY_O: return O;
            case GLFW_KEY_P: return P;
            case GLFW_KEY_Q: return Q;
            case GLFW_KEY_R: return R;
            case GLFW_KEY_S: return S;
            case GLFW_KEY_T: return T;
            case GLFW_KEY_U: return U;
            case GLFW_KEY_V: return V;
            case GLFW_KEY_W: return W;
            case GLFW_KEY_X: return X;
            case GLFW_KEY_Y: return Y;
            case GLFW_KEY_Z: return Z;
            case GLFW_KEY_1: return NUM_1;
            case GLFW_KEY_2: return NUM_2;
            case GLFW_KEY_3: return NUM_3;
            case GLFW_KEY_4: return NUM_4;
            case GLFW_KEY_5: return NUM_5;
            case GLFW_KEY_6: return NUM_6;
            case GLFW_KEY_7: return NUM_7;
            case GLFW_KEY_8: return NUM_8;
            case GLFW_KEY_9: return NUM_9;
            case GLFW_KEY_0: return NUM_0;
            case GLFW_KEY_LEFT_SHIFT: return LEFT_SHIFT;
            case GLFW_KEY_RIGHT_SHIFT: return RIGHT_SHIFT;
            case GLFW_KEY_LEFT_CONTROL: return LEFT_CONTROL;
            case GLFW_KEY_RIGHT_CONTROL: return RIGHT_CONTROL;
            default: return UNKNOWN;
        }
    }

}
