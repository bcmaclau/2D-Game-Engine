#pragma once

#include "engine/scene/component/Transform.h"
#include "engine/scene/component/SingleSprite.h"
#include "engine/scene/component/BoxCollider.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SINGLE_SPRITE,
        BOX_COLLIDER
    };

}
