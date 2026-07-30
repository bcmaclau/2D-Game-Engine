#include "scene/component/Sprite.h"

#include <iostream>

namespace engine::Component {

    void Sprite::init(Transform* t) {
        transform = t;
        sprites = new PointerArrayList<SpriteInfo>();
    }

    void Sprite::shutdown() {
        for (int i = 0; i < sprites->size(); i++) {
            delete (*sprites)[i];
        }
        delete sprites;
    }

    unsigned int Sprite::addSprite(const char* path) {
        SpriteInfo* info = AssetManager::getSprite(path);

        sprites->push_back(info);
        return sprites->size() - 1;
    }

    void Sprite::setActiveSprite(unsigned int id) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        active_id = id;
        active_sprite = (*sprites)[id];
    }

    Vec2 Sprite::getDimensions() const {
        if (active_sprite) { return active_sprite->dimensions; }
        std::cout << "Sprite Component: No sprites added." << std::endl;
        return Vec2(0.0f, 0.0f);
    }

    void Sprite::setDimensions(const Vec2& d) {
        if (active_sprite) { active_sprite->dimensions = d; }
        else { std::cout << "Sprite Component: No sprites added." << std::endl; }
    }

    Vec2 Sprite::getDimensions(unsigned int id) const {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return { 0.0f, 0.0f };
        }
        return (*sprites)[id]->dimensions;
    }

    void Sprite::setDimensions(unsigned int id, const Vec2& d) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->dimensions = d;
    }

    void Sprite::setNumAnimationFrames(int num_frames) {
        if (active_sprite) { active_sprite->frame_width = 1.0f / (float)num_frames; }
        else { std::cout << "Sprite Component: No sprites added." << std::endl; }
    }

    void Sprite::setNumAnimationFrames(unsigned int id, int num_frames) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->frame_width = 1.0f / (float)num_frames;
    }

    void Sprite::setAnimationInterval(int interval) {
        if (active_sprite) { active_sprite->interval = interval; }
        else { std::cout << "Sprite Component: No sprites added." << std::endl; }
    }

    void Sprite::setAnimationInterval(unsigned int id, int interval) {
        if (id < 0 || id >= sprites->size()) {
            std::cout << "Invalid Sprite ID" << std::endl;
            return;
        }
        (*sprites)[id]->interval = interval;
    }

    void Sprite::setCurrentFrame(int frame) {
        if (active_sprite) {
            if (frame < 0 || frame >= 1.0f / active_sprite->frame_width) {
                std::cout << "Invalid Frame Number" << std::endl;
                return;
            }
            active_sprite->current_frame = frame;
        }
        else { std::cout << "Sprite Component: No sprites added." << std::endl; }
    }

    void Sprite::setCurrentFrame(unsigned int id, int frame) {
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

    void Sprite::setRenderLayer(float rl) { render_layer = rl; }

    float Sprite::getRenderLayer() const { return render_layer; }

}
