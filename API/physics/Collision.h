#pragma once

#include <vector>

namespace engine {

    class BaseScene;
    class BaseGameObject;

    class Collision {
    public:
        enum class Side {
            TOP, BOTTOM, LEFT, RIGHT
        }; 

        struct Result {
            BaseGameObject* a, *b;
            Side side;
            float penetration;
        };

        static void init(std::vector<BaseGameObject*>* po, std::vector<Result*>* c);
        static void updateCollisions();
        static void endFrame();
        static void shutdown();

    private:
        Collision() {}

        static bool colliding(BaseGameObject* a, BaseGameObject* b);

        static std::vector<BaseGameObject*>* physics_objects;
        static std::vector<Result*>* collisions;
    };

}
