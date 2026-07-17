#include <engine/Engine.h>

using namespace engine;

class TestObj : public BaseGameObject {
public:
    unsigned int awesomeface_id;

    void onInit() override {
        transform->setPosition(Vec2(1.0f, 2.5f));

        attachComponent(Component::ID::SPRITE);
        awesomeface_id = sprite->addSprite("assets/sprites/awesomeface.png");
        sprite->setDimensions(awesomeface_id, Vec2(1.0f, 1.0f));
        sprite->setActiveSprite(awesomeface_id);
    }
};

class SpaceInvaders : public BaseScene {
public:
    TestObj* t;

    void onInit() override {
        t = instantiate<TestObj>();
    }
};

int main() {
    SpaceInvaders scene;

    Game game;
    game.setWindowDimensions(800, 600);
    game.setNumWorldUnitsVert(5.0f);
    game.setTitle("Space Invaders");    

    game.run(scene);

    return 0;
}
