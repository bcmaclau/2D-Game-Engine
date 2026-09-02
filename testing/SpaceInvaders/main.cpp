#include <engine/Engine.h>

using namespace engine;

class TestObj1 : public BaseGameObject {
public:
    float speed;

    void onInit() override {
        speed = 0.1f;

        transform->setPosition(Vec2(3.0f, 0.0f));

        attachComponent(Component::ID::SPRITE);
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/red_brick.png"));
        sprite->setDimensions(Vec2(1.0f, 1.0f));

        attachComponent(Component::ID::COLLIDER);
        collider->setType(Component::Collider::Type::DYNAMIC);
        //collider->addPointCollider(Vec2(0.0f, 0.0f));
        collider->addBoxCollider(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
    }

    void onFixedUpdate() override {
        Vec2 move_velocity = Vec2(0.0f, 0.0f);
        if (Input::isKeyHeld(Input::Key::A)) {
            move_velocity.x -= speed;
        }
        if (Input::isKeyHeld(Input::Key::D)) {
            move_velocity.x += speed;
        }
        if (Input::isKeyHeld(Input::Key::W)) {
            move_velocity.y += speed;
        }
        if (Input::isKeyHeld(Input::Key::S)) {
            move_velocity.y -= speed;
        }
        collider->setBonusVelocity(move_velocity);
    }

    void onCollisionExit(BaseGameObject* other) override {
        std::cout << "YES" << std::endl;
    }
};

class TestObj2 : public BaseGameObject {
public:
    float speed = 0.3;

    void onInit() override {
        attachComponent(Component::ID::SPRITE);
        sprite->setActiveSprite(sprite->addSprite("assets/sprites/red_brick.png"));
        sprite->setDimensions(Vec2(1.0f, 1.0f));

        attachComponent(Component::ID::COLLIDER);
        collider->setType(Component::Collider::Type::DYNAMIC);
        collider->addBoxCollider(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
    }

    void onFixedUpdate() override {
        Vec2 move_velocity = Vec2(0.0f, 0.0f);
        if (Input::isKeyHeld(Input::Key::LEFT)) {
            move_velocity.x -= speed;
        }
        if (Input::isKeyHeld(Input::Key::RIGHT)) {
            move_velocity.x += speed;
        }
        if (Input::isKeyHeld(Input::Key::UP)) {
            move_velocity.y += speed;
        }
        if (Input::isKeyHeld(Input::Key::DOWN)) {
            move_velocity.y -= speed;
        }
        collider->setBonusVelocity(move_velocity);
    }
};

class TestScene : public BaseScene {
public:
    TestObj1* obj_1;
    TestObj2* obj_2;

    void useSprites() override {
        addSpriteDirectory("assets/sprites", true);
    }

    void onInit() override {
        unsigned int cg = createNewCollisionGroup();

        obj_1 = instantiateGameObject<TestObj1>();
        obj_2 = instantiateGameObject<TestObj2>();

        moveToCollisionGroup(obj_1, cg);
    }

};

int main() {
    TestScene scene;
    Game game;
    game.setTitle("uhhhhh");
    game.run(scene);

    return 0;
}
