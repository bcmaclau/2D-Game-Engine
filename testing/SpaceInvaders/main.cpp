#include <engine/Engine.h>

using namespace engine;

class Ship : public BaseGameObject {
public:
    int ship_sprite;

    float speed;

    void onInit() override {
        speed = 5.0f;

        transform->setPosition(Vec2(400.0f, 100.0f));

        attachComponent(Component::ID::SPRITE);
        ship_sprite = sprite->addSprite("assets/sprites/awesomeface.png");
        sprite->setRenderLayer(Component::Sprite::RenderLayer::ENTITY);
        sprite->setDimensions(ship_sprite, Vec2(64.0f, 64.0f));
        sprite->setActiveSprite(ship_sprite);
    }

    void onFixedUpdate() override {
        if (Input::isKeyHeld(Input::Key::A)) {
            transform->move(Vec2(-speed, 0.0f));
        }
        if (Input::isKeyHeld(Input::Key::D)) {
            transform->move(Vec2(speed, 0.0f));
        }
        if (Input::isKeyHeld(Input::Key::W)) {
            transform->move(Vec2(0.0f, speed));
        }
        if (Input::isKeyHeld(Input::Key::S)) {
            transform->move(Vec2(0.0f, -speed));
        }
    }
};

class Env : public BaseGameObject {
public:
    int ship_sprite;

    void onInit() override {
        transform->setPosition(Vec2(350.0f, 100.0f));

        attachComponent(Component::ID::SPRITE);
        ship_sprite = sprite->addSprite("assets/sprites/awesomeface.png");
        sprite->setRenderLayer(Component::Sprite::RenderLayer::ENVIRONMENT);
        sprite->setDimensions(ship_sprite, Vec2(64.0f, 64.0f));
        sprite->setActiveSprite(ship_sprite);
    }
};

class SpaceInvaders : public BaseScene {
public:
Env* env;
    Ship* ship;

    void onInit() override {
        ship = instantiate<Ship>();
        env = instantiate<Env>();
    }
};

int main() {
    SpaceInvaders scene;

    Game game;
    game.setWindowDimensions(800, 600);
    game.setTitle("Space Invaders");

    game.run(scene);

    return 0;
}
