#include <engine/Engine.h>

#include <iostream>

class TestGame : public engine::Game {
public:
    engine::Texture tex;
    glm::vec2 position;
    float velocity;

    void onInit() override {
        tex.init("assets/sprites/awesomeface.png");
        position = glm::vec2(50.0f, 50.0f);
        velocity = 3.0f;
    }

    void onUpdate(float dt) override {
        if (engine::Input::isKeyHeld(engine::Key::LEFT)) {
            position.x -= velocity;
        }
        if (engine::Input::isKeyHeld(engine::Key::RIGHT)) {
            position.x += velocity;
        }
        if (engine::Input::isKeyHeld(engine::Key::DOWN)) {
            position.y -= velocity;
        }
        if (engine::Input::isKeyHeld(engine::Key::UP)) {
            position.y += velocity;
        }
    }    

    void onRender() override {
        sprite_renderer.draw(&tex, position, {100.0f, 100.0f});
    }

    void onShutdown() override {
        tex.shutdown();
    }
};

int main() {
    TestGame game;
    game.run();

    return 0;
}