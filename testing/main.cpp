#include <engine/Engine.h>

#include "Players.h"

#include <iostream>

class TestGame : public engine::Game {
public:
    Player1* p1;
    Player2* p2;

    void onInit() override {
        p1 = scene.instantiateGameObject<Player1>();

        p2 = scene.instantiateGameObject<Player2>();
    }

    void onUpdate(float dt) override {
        engine::CollisionResult col = engine::Collision::AABBCollisionDetailed(*p1, *p2);

        if (col.collided) {
            switch (col.side) {
                case engine::CollisionSide::LEFT:
                    std::cout << "left" << std::endl;
                    break;
                case engine::CollisionSide::RIGHT:
                    std::cout << "right" << std::endl;
                    break;
                case engine::CollisionSide::TOP:
                    std::cout << "top" << std::endl;
                    break;
                default:
                    std::cout << "bottom" << std::endl;
                    break;
            }
        }
    }    

    void onRender() override {
        
    }

    void onShutdown() override {

    }
};

int main() {
    TestGame game;
    game.run();

    return 0;
}