#include "scene/component/Sprite.h"

#include <iostream>

namespace engine::Component {

    void Sprite::init(AssetManager* a) {
        assets = a;
        sprites = new PointerList<Details>;
    }

    void Sprite::shutdown() {
        for (int i = 0; i < sprites->size(); i++) {
            delete (*sprites)[i];
        }
        delete sprites;
    }

    int Sprite::addSprite(const char* path) {
        Details* details = new Details();
        if (assets) {
            details->texture = assets->loadTexture(path);
        }
        else {
            std::cout << "Failed to add sprite, component uninitialized" << std::endl;
            return -1;
        }
        details->current_frame = 0;
        details->frame_width = 1.0f;
        details->interval = 0.0f;
        
        sprites->push_back(details);
        active_sprite = (*sprites)[active_id];

        return (int)sprites->size() - 1;
    }

    void Sprite::setActiveSprite(int id) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        active_id = id;
        active_sprite = (*sprites)[id];
    }

    Vec2 Sprite::getDimensions(int id) const {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return { 0.0f, 0.0f };
        }
        return (*sprites)[id]->dimensions;
    }

    void Sprite::setDimensions(int id, const Vec2& d) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->dimensions = d;
    }

    void Sprite::setNumAnimationFrames(int id, int num_frames) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->frame_width = 1.0f / (float)num_frames;
    }

    void Sprite::setAnimationInterval(int id, int interval) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->interval = interval;
    }

    void Sprite::setCurrentFrame(int id, int frame) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        if (frame < 0 || frame >= 1.0f / (*sprites)[id]->frame_width) {
            std::cout << "Invalid Frame Number" << std::endl;
            return;
        }
        (*sprites)[id]->current_frame = frame;
    }

}
