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
        Sprite() : active_id(0), active_sprite(nullptr), sprites(nullptr), render_layer(0.0f) {}
        ~Sprite() {}

        unsigned int addSprite(const char* path);
        void setActiveSprite(int id);

        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);
        Vec2 getDimensions(int id) const;
        void setDimensions(int id, const Vec2& d);

        void setNumAnimationFrames(int num_frames);
        void setNumAnimationFrames(int id, int num_frames);

        void setAnimationInterval(int interval);
        void setAnimationInterval(int id, int interval);

        void setCurrentFrame(int frame);
        void setCurrentFrame(int id, int frame);

        void setRenderLayer(float rl);
        float getRenderLayer() const;

    private:
        AssetManager* assets;

        struct Details {
            Vec2 dimensions = { 1.0f, 1.0f };
            Texture* texture = nullptr;
            int current_frame = 0;
            float frame_width = 1.0f;
            int interval = 0;
            int interval_acc = 0;
        };

        int active_id;
        Details* active_sprite;
        PointerArrayList<Details>* sprites;
        float render_layer;

        void init(AssetManager* a);
        void shutdown();
    };

}
