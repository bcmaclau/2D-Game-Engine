#include "scene/component/SingleSprite.h"

namespace engine::Component {

    Texture* SingleSprite::getTexture() const { return texture; }
    void SingleSprite::setTexture(const char* path) {
        if (assets) {
            texture = assets->loadTexture(path);
        }
    }

    Vec2 SingleSprite::getDimensions() const { return dimensions; }
    void SingleSprite::setDimensions(const Vec2& d) { dimensions = d; }

}
