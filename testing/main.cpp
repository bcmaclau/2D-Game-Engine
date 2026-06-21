#include <engine/Engine.h>

#include "Players.h"

class TestGame : public engine::Game {
public:
    Player1* p1;
    Player2* p2;

    void onInit() override {
        p1 = scene.instantiateGameObject<Player1>();

        p2 = scene.instantiateGameObject<Player2>();
    }

    void onUpdate(float dt) override {
        
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