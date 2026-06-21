#include <engine/Engine.h>

class Player1 : public engine::GameObject {
public:
    float speed;

    void onInit() override {
        setTexture("assets/sprites/awesomeface.png");
        setPosition({200.0f, 300.0f});
        setSize({100.0f, 100.0f});
        speed = 5.0f;
    }

    void onUpdate(float dt) override {
        if (engine::Input::isKeyHeld(engine::Key::W)) {
            move({0.0f, speed});
        }
        if (engine::Input::isKeyHeld(engine::Key::S)) {
            move({0.0f, -speed});
        }
        if (engine::Input::isKeyHeld(engine::Key::A)) {
            move({-speed, 0.0f});
        }
        if (engine::Input::isKeyHeld(engine::Key::D)) {
            move({speed, 0.0f});
        }
    }
};

class Player2 : public engine::GameObject {
public:
    float speed;

    void onInit() override {
        setTexture("assets/sprites/awesomeface.png");
        setPosition({600.0f, 300.0f});
        setSize({100.0f, 100.0f});
        speed = 5.0f;
    }

    void onUpdate(float dt) override {
        if (engine::Input::isKeyHeld(engine::Key::UP)) {
            move({0.0f, speed});
        }
        if (engine::Input::isKeyHeld(engine::Key::DOWN)) {
            move({0.0f, -speed});
        }
        if (engine::Input::isKeyHeld(engine::Key::LEFT)) {
            move({-speed, 0.0f});
        }
        if (engine::Input::isKeyHeld(engine::Key::RIGHT)) {
            move({speed, 0.0f});
        }
    }
};
