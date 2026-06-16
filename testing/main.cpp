#include <engine/Engine.h>

#include <iostream>

class TestGame : public engine::Game {
public:
    void onUpdate(float dt) override {
        std::cout << "Current FPS: " << 1 / dt << std::endl;
    }
};

int main() {
    TestGame game;
    game.run();

    return 0;
}