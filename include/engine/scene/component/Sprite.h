#pragma once

#include "engine/scene/BaseScene.h"
#include "engine/scene/BaseGameObject.h"
#include "engine/data_structures/Vector.h"

#include <vector>

namespace engine {

    class Texture;
    class BatchRenderer;
    class SpriteInfo;

}

namespace engine::Component {

    class Sprite {
        friend class engine::BaseScene;
        friend class engine::BaseGameObject;
        friend class engine::BaseUIObject;
        friend class engine::BatchRenderer;
    
    public:
        Sprite() : active_id(0), active_sprite(nullptr), sprites(nullptr), render_layer(0.0f) {}
        ~Sprite() {}

        unsigned int addSprite(const char* path);
        void setActiveSprite(unsigned int id);

        Vec2 getDimensions() const;
        void setDimensions(const Vec2& d);
        Vec2 getDimensions(unsigned int id) const;
        void setDimensions(unsigned int id, const Vec2& d);

        void setNumAnimationFrames(int num_frames);
        void setNumAnimationFrames(unsigned int id, int num_frames);

        void setAnimationInterval(int interval);
        void setAnimationInterval(unsigned int id, int interval);

        void setCurrentFrame(int frame);
        void setCurrentFrame(unsigned int id, int frame);

        void setRenderLayer(float rl);
        float getRenderLayer() const;

    private:
        unsigned int active_id;
        Transform* transform;
        SpriteInfo* active_sprite;
        PointerArrayList<SpriteInfo>* sprites;
        
        float render_layer;
        PLLNode<Sprite>* order_node;

        void init(Transform* t);
        void shutdown();
    };

}
