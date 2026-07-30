#pragma once

#include "renderer/AssetManager.h"
#include "renderer/Texture.h"
#include "renderer/BatchRenderer.h"
#include "math/Vector.h"
#include "data_structures/PointerArrayList.h"
#include "data_structures/PointerLinkedList.h"
#include "scene/component/Transform.h"

namespace engine {

    class BaseScene;
    class BaseGameObject;
    class BaseUIObject;
    class SpriteRenderer;

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

        int active_id;
        Transform* transform;
        SpriteInfo* active_sprite;
        PointerArrayList<SpriteInfo>* sprites;
        
        float render_layer;
        PLLNode<Sprite>* order_node;

        void init(AssetManager* a, Transform* t);
        void shutdown();
    };

}
