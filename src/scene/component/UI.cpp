#include "scene/component/UI.h"

namespace engine::Component {

    Vec2 UI::getDimensions() const {
        return dimensions;
    }

    void UI::setDimensions(const Vec2& d) {
        dimensions = d;
    }

}
