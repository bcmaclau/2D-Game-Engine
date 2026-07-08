#pragma once

#include "container/PointerList.h"

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

        static void init(PointerList<BaseGameObject>* po, PointerList<Result>* c);
        static void updateCollisions();
        static void endFrame();
        static void shutdown();

    private:
        Collision() {}

        static bool colliding(BaseGameObject* a, BaseGameObject* b);

        static PointerList<BaseGameObject>* physics_objects;
        static PointerList<Result>* collisions;
    };

}
