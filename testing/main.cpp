#include <engine/Engine.h>

#include <iostream>

class AwesomeFace : public engine::BaseGameObject {
public:
    int spawn;

    void onInit() override {
        spawn = 0;

        transform->setPosition({ 100.0f, 100.0f });

        attachComponent(engine::component::ID::SINGLE_SPRITE);
        single_sprite->setTexture("assets/sprites/awesomeface.png");
        single_sprite->setDimensions({ 100.0f, 100.0f });
    }

    void onUpdate(float dt) override {
        if (engine::Input::isKeyPushed(engine::Input::Key::SPACE)) {
            if (spawn == 0) {
                BaseGameObject* obj = instantiateOther<AwesomeFace>();
                obj->transform->setPosition(transform->getPosition());
                obj->transform->move({ 100.0f, 0.0f });
            }
            else if (spawn == 2) {
                destroySelf();
            }
            spawn++;
        }
    }
};

class TestScene : public engine::BaseScene {
public:
    AwesomeFace* awesome_face;

    void onInit() override {
        awesome_face = instantiate<AwesomeFace>();
    }
};

int main() {
    TestScene first_scene;

    engine::Game game;
    game.run(first_scene);

    return 0;
}