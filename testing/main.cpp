#include <engine/Engine.h>

#include <iostream>

class TestGame : public engine::Game {
public:
    engine::Texture tex;
    glm::vec2 position;

    void onInit() override {
        tex.init("assets/sprites/awesomeface.png");
        position = glm::vec2(50.0f, 50.0f);
    }

    void onRender() override {
        sprite_renderer.draw(&tex, position, {100.0f, 100.0f});
    }

    void onUpdate(float dt) override {
        position.x += 1.0f;
    }
};

int main() {
    TestGame game;
    game.run();

    return 0;
}