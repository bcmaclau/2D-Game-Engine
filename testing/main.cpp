#include <engine/Engine.h>

#include <iostream>

class TestPlayer : public engine::BaseGameObject {
public:
    float speed;

    void onInit() override {
        speed = 3.0f;

        transform->setPosition({ 100.0f, 100.0f });

        attachComponent(engine::Component::ID::SINGLE_SPRITE);
        single_sprite->setTexture("assets/sprites/awesomeface.png");
        single_sprite->setDimensions({ 100.0f, 100.0f });

        attachComponent(engine::Component::ID::BOX_COLLIDER);
        box_collider->setDimensions({ 100.0f, 100.0f });
    }

    void onFixedUpdate() override {
        if (engine::Input::isKeyHeld(engine::Input::Key::W)) {
            transform->move({ 0.0f, speed });
        }
        if (engine::Input::isKeyHeld(engine::Input::Key::S)) {
            transform->move({ 0.0f, -speed });
        }
        if (engine::Input::isKeyHeld(engine::Input::Key::A)) {
            transform->move({ -speed, 0.0f });
        }
        if (engine::Input::isKeyHeld(engine::Input::Key::D)) {
            transform->move({ speed, 0.0f });
        }
    }

    void onCollision(BaseGameObject* other, engine::Collision::Side side, float penetration) override {
        switch (side) {
            case engine::Collision::Side::TOP:
                std::cout << "top" << std::endl;
                break;
            case engine::Collision::Side::BOTTOM:
                std::cout << "bottom" << std::endl;
                break;
            case engine::Collision::Side::LEFT:
                std::cout << "left" << std::endl;
                break;
            default:
                std::cout << "right" << std::endl;
                break;
        }
    }
};

class TestBlock : public engine::BaseGameObject {
public:
    void onInit() override {
        transform->setPosition({ 300.0f, 300.0f });

        attachComponent(engine::Component::ID::SINGLE_SPRITE);
        single_sprite->setTexture("assets/sprites/awesomeface.png");
        single_sprite->setDimensions({ 100.0f, 100.0f });

        attachComponent(engine::Component::ID::BOX_COLLIDER);
        box_collider->setDimensions({ 100.0f, 100.0f });
    }
};

class TestScene : public engine::BaseScene {
public:
    TestPlayer* player;
    TestBlock* block;

    void onInit() override {
        player = instantiate<TestPlayer>();
        block = instantiate<TestBlock>();
    }

    void onUpdate(float dt) override {
        if (engine::Input::isKeyHeld(engine::Input::Key::ESCAPE)) {
            endGame();
        }
    }
};

int main() {
    TestScene first_scene;

    engine::Game game;
    game.run(first_scene);

    return 0;
}