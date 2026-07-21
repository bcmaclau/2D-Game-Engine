#include <engine/Engine.h>

#include <iostream>

using namespace engine;

class Brick : public BaseGameObject {
public:
    unsigned int brick_id;

    void onInit() override {
        attachComponent(Component::ID::SPRITE);
        brick_id = sprite->addSprite("assets/sprites/red_brick.png");
        sprite->setDimensions(brick_id, Vec2(48.0f, 16.0f));
        sprite->setActiveSprite(brick_id);

        attachComponent(Component::ID::BOX_COLLIDER);
        box_collider->setDimensions(Vec2(48.0f, 16.0f));

        setTag(1);
    }
};

class Ball : public BaseGameObject {
public:
    unsigned int ball_id;
    bool h, v;
    float speed;
    Vec2 velocity;

    void onInit() override {
        h = false;
        v = false;

        speed = 3.0f;
        velocity = Vec2(0.0f, -speed);

        transform->setPosition(Vec2(400.0f, 300.0f));

        attachComponent(Component::ID::SPRITE);
        ball_id = sprite->addSprite("assets/sprites/ball.png");
        sprite->setDimensions(ball_id, Vec2(16.0f, 16.0f));
        sprite->setActiveSprite(ball_id);

        attachComponent(Component::ID::BOX_COLLIDER);
        box_collider->setDimensions(Vec2(16.0f, 16.0f));
    }

    void onUpdate(float dt) override {
        h = false;
        v = false;
    }

    void onFixedUpdate() override {
        transform->move(velocity);

        if (transform->getPosition().x >= 800 - 8) {
            transform->setPosition(Vec2(800 - 8, transform->getPosition().y));
            velocity.x *= -1.0f;
        }
        if (transform->getPosition().x <= 8) {
            transform->setPosition(Vec2(8, transform->getPosition().y));
            velocity.x *= -1.0f;
        }
        if (transform->getPosition().y >= 600 - 8) {
            transform->setPosition(Vec2(transform->getPosition().x, 600 - 8));
            velocity.y *= -1.0f;
        }
        if (transform->getPosition().y <= 8) {
            transform->setPosition(Vec2(transform->getPosition().x, 8));
            velocity.y *= -1.0f;
        }
    }

    void onCollision(BaseGameObject* other, Collision::Side side, float penetration) override {
        // for one collision horizontally and vertically per frame, adjust for the overlapping space and flip velocity
        if (!h) {
            if (side == Collision::Side::LEFT) {
                transform->move(Vec2(penetration, 0.0f));
                if (other->getTag() == 1) { velocity.x *= -1.0f; }
                h = true;
            }
            else if (side == Collision::Side::RIGHT) {
                transform->move(Vec2(-penetration, 0.0f));
                if (other->getTag() == 1) { velocity.x *= -1.0f; }
                h = true;
            }
        }
        if (!v) {
            if (side == Collision::Side::BOTTOM) {
                transform->move(Vec2(0.0f, penetration));
                if (other->getTag() == 1) { velocity.y *= -1.0f; }
                v = true;
            }
            else if (side == Collision::Side::TOP) {
                transform->move(Vec2(0.0f, -penetration));
                if (other->getTag() == 1) { velocity.y *= -1.0f; }
                v = true;
            }
        }

        if (other->getTag() == 1) {
            destroyGameObject(other);
        }
        else if (other->getTag() == 2) {
            if (side == Collision::Side::BOTTOM) {
                velocity = Vec2::normalize(transform->getPosition() - other->transform->getPosition()) * speed;
            }
            else if (side == Collision::Side::LEFT || side == Collision::Side::RIGHT) {
                velocity.x *= -1.0f;
            }
        }
    }
};

class Paddle : public BaseGameObject {
public:
    unsigned int paddle_id;
    float speed;

    void onInit() override {
        speed = 3.0f;

        transform->setPosition(Vec2(400.0f, 100.0f));

        attachComponent(Component::ID::SPRITE);
        paddle_id = sprite->addSprite("assets/sprites/paddle.png");
        sprite->setDimensions(paddle_id, Vec2(48.0f, 16.0f));
        sprite->setActiveSprite(paddle_id);

        attachComponent(Component::ID::BOX_COLLIDER);
        box_collider->setDimensions(Vec2(48.0f, 16.0f));

        setTag(2);
    }

    void onFixedUpdate() override {
        if (Input::isKeyHeld(Input::Key::LEFT)) {
            transform->move(Vec2(-speed, 0.0f));
        }
        if (Input::isKeyHeld(Input::Key::RIGHT)) {
            transform->move(Vec2(speed, 0.0f));
        }
    }
};

class Breakout : public BaseScene {
public:
    Ball* ball;
    Paddle* paddle;
    Brick* bricks[8][14];

    void onInit() override {
        ball = instantiateGameObject<Ball>();
        paddle = instantiateGameObject<Paddle>();

        float x = 62.0f, y = 588.0f;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 14; j++) {
                bricks[i][j] = instantiateGameObject<Brick>();
                bricks[i][j]->transform->setPosition(Vec2(x, y));
                x += 52.0f;
            }
            x = 62.0f;
            y -= 20.0f;
        }
    }
};

int main() {
    Breakout first_scene;

    engine::Game game;
    game.setTitle("Breakout");
    game.setWindowDimensions(800, 600);

    game.run(first_scene);

    return 0;
}