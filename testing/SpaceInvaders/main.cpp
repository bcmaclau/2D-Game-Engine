#include <engine/Engine.h>

using namespace engine;

class TestUIObj : public BaseUIObject {
    void onInit() {
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/red_brick.png"));
        sprite->setDimensions(Vec2(1.0f, 1.0f));
    }
};

class TestGameObj : public BaseGameObject {
public:
    float speed;

    void onInit() {
        speed = 0.1f;

        attachComponent(Component::ID::SPRITE);
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/more/awesomeface.png"));
        sprite->setDimensions(Vec2(2.0f, 2.0f));
    }

    void onFixedUpdate() override {
        if (Input::isKeyHeld(Input::Key::A)) { transform->move(Vec2(-speed, 0.0f)); }
        if (Input::isKeyHeld(Input::Key::D)) { transform->move(Vec2(speed, 0.0f)); }
        if (Input::isKeyHeld(Input::Key::W)) { transform->move(Vec2(0.0f, speed)); }
        if (Input::isKeyHeld(Input::Key::S)) { transform->move(Vec2(0.0f, -speed)); }
    }
};

class TestScene : public BaseScene {
public:
    TestUIObj* ui_obj;
    TestGameObj* game_obj;

    void useSprites() override {
        addSpriteDirectory("assets/sprites", true);
    }

    void onInit() {
        ui_obj = instantiateUIObject<TestUIObj>();
        game_obj = instantiateGameObject<TestGameObj>();
        //cameraFollow(game_obj);
    }
};

int main() {
    TestScene scene;
    Game game;
    game.setTitle("uhhhhh");
    game.run(scene);

    return 0;
}
