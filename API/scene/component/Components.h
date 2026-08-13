#pragma once

#include "scene/component/Transform.h"
#include "scene/component/Sprite.h"
#include "scene/component/Collider.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SPRITE,
        COLLIDER
    };

}
