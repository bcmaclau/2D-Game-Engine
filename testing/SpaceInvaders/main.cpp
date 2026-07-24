#include <engine/Engine.h>

using namespace engine;

class BrickObj : public BaseGameObject {
public:
    void onInit() override {
        transform->setPosition(Vec2(2.0f, 2.0f));

        attachComponent(Component::ID::SPRITE);
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/red_brick.png"));
        sprite->setDimensions(Vec2(1.0f, 1.0f));
    }
};

class BrickUI : public BaseUIObject {
public:
    void onInit() override {
        //transform->setPosition(Vec2(40.0f / 6.0f, 5.0f));

        sprite->setActiveSprite(sprite->addSprite("assets/sprites/red_brick.png"));
        sprite->setDimensions(Vec2(1.0f, 4.9f));
        sprite->setRenderLayer(55.0f);
    }

    void onClickExit(Input::Button button) {
        if (button == Input::Button::LEFT) {
            std::cout << "oh tyeah" << std::endl;
        }
    }
};

class FaceObj : public BaseGameObject {
public:
    float speed;

    bool a;
    BrickUI* obj;    

    void onInit() override {
        speed = 0.1f;
        a = false;

        attachComponent(Component::ID::SPRITE);
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/awesomeface.png"));
        sprite->setDimensions(Vec2(1.0f, 1.0f));
        sprite->setRenderLayer(1.0f);
    }

    void onFixedUpdate() override {
        if (Input::isKeyHeld(Input::Key::W)) { transform->move(Vec2(0.0f, speed)); }
        if (Input::isKeyHeld(Input::Key::S)) { transform->move(Vec2(0.0f, -speed)); }
        if (Input::isKeyHeld(Input::Key::A)) { transform->move(Vec2(-speed, 0.0f)); }
        if (Input::isKeyHeld(Input::Key::D)) { transform->move(Vec2(speed, 0.0f)); }
    }

    void onUpdate(float dt) override {
        if (Input::isKeyPushed(Input::Key::R)) {
            if (!a) { obj = instantiateUIObject<BrickUI>(); a = true; }
            else { destroyUIObject(obj); a = false; }
        }
    }
};

class SpaceInvaders : public BaseScene {
public:
    FaceObj* face;
    BrickObj* brick;
    BrickUI* ui;

    void onInit() override {
        //face = instantiateGameObject<FaceObj>();
        //brick = instantiateGameObject<BrickObj>();
        ui = instantiateUIObject<BrickUI>();
    }

    void onUpdate(float dt) override {
        //Vec2 m = Input::getMousePos();
        //std::cout << "Mouse: " << m.x << ", " << m.y << std::endl;
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
