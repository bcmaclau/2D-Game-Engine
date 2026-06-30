#pragma once

#include "scene/component/Transform.h"
#include "scene/component/SingleSprite.h"
#include "scene/component/BoxCollider.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SINGLE_SPRITE,
        BOX_COLLIDER
    };

}
