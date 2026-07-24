#pragma once

#include "scene/component/Transform.h"
#include "scene/component/Sprite.h"

namespace engine {

    class UIInteraction {
    public:
        static bool isHovering(Component::Transform* transform, Component::Sprite* sprite);

    private:
        UIInteraction() {};
        
    };

}
