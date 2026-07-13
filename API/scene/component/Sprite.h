#pragma once

#include "renderer/AssetManager.h"
#include "renderer/Texture.h"
#include "math/Vector.h"
#include "container/PointerList.h"

namespace engine {

    class BaseScene;
    class BaseGameObject;
    class SpriteRenderer;

}

namespace engine::Component {

    class Sprite {
        friend class engine::BaseScene;
        friend class engine::BaseGameObject;
        friend class engine::SpriteRenderer;
    
    public:
        Sprite() : active_id(0), active_sprite(nullptr), sprites(nullptr), render_layer(RenderLayer::BACKGROUND), layer_index(0), layer_set(false) {}
        ~Sprite() {}

        int addSprite(const char* path);
        void setActiveSprite(int id);

        Vec2 getDimensions(int id) const;
        void setDimensions(int id, const Vec2& d);
        void setNumAnimationFrames(int id, int num_frames);
        void setAnimationInterval(int id, int interval);
        void setCurrentFrame(int id, int frame);

        enum class RenderLayer {
            BACKGROUND, ENVIRONMENT, ENTITY, UI
        };
        void setRenderLayer(RenderLayer layer);
        RenderLayer getRenderLayer() const;

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
        PointerList<Details>* sprites;
        RenderLayer render_layer;
        unsigned int layer_index;
        bool layer_set;

        void init(AssetManager* a);
        void shutdown();
    };

}
