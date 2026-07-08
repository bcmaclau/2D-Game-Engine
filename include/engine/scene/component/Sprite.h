#pragma once

#include "engine/scene/BaseScene.h"
#include "engine/scene/BaseGameObject.h"
#include "engine/math/Vector.h"

#include <vector>

namespace engine {

    class Texture;

}

namespace engine::Component {

    class Sprite {
        friend class engine::BaseScene;
        friend class engine::BaseGameObject;
        friend class engine::SpriteRenderer;
    
    public:
        Sprite() {}
        ~Sprite() {}

        int addSprite(const char* path);
        void setActiveSprite(int id);

        Vec2 getDimensions(int id) const;
        void setDimensions(int id, const Vec2& d);

        void setNumAnimationFrames(int id, int num_frames);
        void setAnimationInterval(int id, int);
        void setCurrentFrame(int id, int frame);

    private:
        AssetManager* assets;

        struct Details {
            Vec2 dimensions;
            Texture* texture;
            int current_frame;
            float frame_width;
            int interval;
            int interval_acc;
        };

        int active_id;
        Details active_sprite;
        std::vector<Details> sprites;
    };

}
