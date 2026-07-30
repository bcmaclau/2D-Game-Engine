#include "input/UIInteraction.h"

#include "data_structures/Vector.h"
#include "input/Input.h"


namespace engine {

    bool UIInteraction::isHovering(Component::Transform* transform, Component::Sprite* sprite) {
        Vec2 m = Input::getMousePos(), p = transform->getPosition(), d = sprite->getDimensions() / 2.0f;
        return m.x >= (p.x - d.x) && m.x <= (p.x + d.x) && m.y >= (p.y - d.y) && m.y <= (p.y + d.y);
    }

}
