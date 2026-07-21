#pragma once

#include "data_structures/PointerArrayList.h"

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

        static void init(PointerArrayList<BaseGameObject>* po, PointerArrayList<Result>* c);
        static void updateCollisions();
        static void endFrame();
        static void shutdown();

    private:
        Collision() {}

        static bool colliding(BaseGameObject* a, BaseGameObject* b);

        static PointerArrayList<BaseGameObject>* physics_objects;
        static PointerArrayList<Result>* collisions;
    };

}
