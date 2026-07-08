#pragma once

#include "engine/scene/component/Transform.h"
#include "engine/scene/component/Sprite.h"
#include "engine/scene/component/BoxCollider.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SPRITE,
        BOX_COLLIDER
    };

}
