#pragma once

#include "scene/component/Transform.h"
#include "scene/component/Sprite.h"
#include "scene/component/BoxCollider.h"
#include "scene/component/UI.h"

namespace engine::Component {

    enum class ID {
        TRANSFORM,
        SPRITE,
        BOX_COLLIDER,
        UI
    };

}
