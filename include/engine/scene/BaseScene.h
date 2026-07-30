#pragma once

#include "engine/data_structures/Vector.h"
#include "engine/data_structures/PointerArrayList.h"
#include "engine/data_structures/PointerLinkedList.h"
#include "engine/scene/BaseGameObject.h"

namespace engine {

    // NOTE: Forward declarations are used to hide implementation details
    // All "private" classes need to be forward declared and are implemented as pointers
    // This is because memory allocation only needs 8 bytes for a pointer, but an unknown amount for the actual object
    // I could use a pimpl struct to work around the pointers, but they need to be initialized on the heap in the constructor
    // This won't work for all my classes; some are static with private construtors (and I think the syntax is ugly)
    // The downside is that whenever I make a change to any API headers, I will need to update these public headers
    // I would've had to anyway if I used pimpl
    // However I need to #include <vector> which wouldn't happen if I use pimpl, might switch later

    class AssetManager;
    class SpriteRenderer;
    class Camera2D;

    class BaseUIObject;

    namespace Collision {
        enum class Side {
            TOP, BOTTOM, LEFT, RIGHT
        };
        struct Result;
    }

    class BaseScene {
        friend class Game;

    public:
        BaseScene() : swap_scene(false), new_scene(nullptr), end_game(false), in_use_sprites(true),
        camera(nullptr), camera_follow(nullptr),
        game_objects(nullptr), go_to_instantiate(nullptr), ui_to_instantiate(nullptr), physics_objects(nullptr), collisions(nullptr) {}
        virtual ~BaseScene() {}

        template <typename T>
        void swapScene() {
            static_assert(std::is_base_of<BaseScene, T>::value, "T must derive from BaseScene");

            new_scene = new T();
            swap_scene = true;
        }

        void endGame();

        template <typename T>
        T* instantiateGameObject() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(screen_width_units, screen_height_units, game_objects->size(), go_to_instantiate, ui_to_instantiate);
            go_to_instantiate->push_back(obj);
            return obj;
        }
        void destroyGameObject(BaseGameObject* obj);

        template <typename T>
        T* instantiateUIObject() {
            static_assert(std::is_base_of<BaseUIObject, T>::value, "T must derive from BaseUIObject");

            T* obj = new T();
            obj->init(screen_width_units, screen_height_units, ui_objects->size(), go_to_instantiate, ui_to_instantiate);
            ui_to_instantiate->push_back(obj);
            return obj;
        }
        void destroyUIObject(BaseUIObject* obj);

        Vec2 getScreenDimensions() const;

        Vec2 getCameraPosition() const;
        void setCameraPosition(const Vec2& pos);
        void moveCamera(const Vec2& delta);
        void cameraFollow(BaseGameObject* obj);
        void cameraUnfollow();

        void addSpriteDirectory(const char* path, bool recurse);

    protected:
        // user implemented functions
        virtual void useSprites() {}
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(unsigned int sw, unsigned int sh, float suv);
        void update(float dt);
        void handlePhysics();
        void handleUI();
        void fixedUpdate();
        void draw();
        void endFrame();
        void shutdown();

        unsigned int screen_width_pixels, screen_height_pixels;
        float screen_width_units, screen_height_units;
        bool swap_scene;
        BaseScene* new_scene;
        bool end_game;
        bool in_use_sprites;

        Camera2D* camera;
        BaseGameObject* camera_follow;

        PointerArrayList<BaseGameObject>* game_objects;
        PointerArrayList<BaseGameObject>* go_to_instantiate;

        PointerArrayList<BaseUIObject>* ui_objects;
        PointerArrayList<BaseUIObject>* ui_to_instantiate;

        PointerLinkedList<Component::Sprite>* go_render_order;
        PointerLinkedList<Component::Sprite>* ui_render_order;

        PointerArrayList<BaseGameObject>* physics_objects;
        PointerArrayList<Collision::Result>* collisions;

        void removeGOFromLists(BaseGameObject* obj);
        void removeUIFromList(BaseUIObject* obj);
        PLLNode<Component::Sprite>* insertSpriteToRO(Component::Sprite* sprite, PointerLinkedList<Component::Sprite>* render_order);
    };

}
