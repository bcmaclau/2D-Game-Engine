#pragma once

#include <vector>

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

    class BaseGameObject;

    template <typename T>
    class PointerList {
    public:
        void push_back(T* data);
        unsigned int size() const;
    };

    namespace Collision {
        enum class Side {
            TOP, BOTTOM, LEFT, RIGHT
        };
        struct Result;
    }

    class BaseScene {
        friend class Game;

    public:
        BaseScene() : swap_scene(false), new_scene(nullptr), end_game(false),
        assets(nullptr), sprite_renderer(nullptr), camera(nullptr) {}
        virtual ~BaseScene() = default;

        template <typename T>
        void swapScene() {
            static_assert(std::is_base_of<BaseScene, T>::value, "T must derive from BaseScene");

            new_scene = new T();
            swap_scene = true;
        }

        void endGame();

        template <typename T>
        T* instantiate() {
            static_assert(std::is_base_of<BaseGameObject, T>::value, "T must derive from BaseGameObject");

            T* obj = new T();
            obj->init(assets, screen_width, screen_height, game_objects->size(), to_instantiate, physics_objects);
            game_objects->push_back(obj);
            return obj;
        }
        void destroy(BaseGameObject* obj);

        Vec2 getScreenDimensions() const;

    protected:
        // user implemented functions
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, unsigned int sw, unsigned int sh);
        void update(float dt);
        void fixedUpdate();
        void draw();
        void endFrame();
        void shutdown();

        void dynamicInstantiate(BaseGameObject* obj);

        unsigned int screen_width, screen_height;
        bool swap_scene;
        BaseScene* new_scene;
        bool end_game;

        AssetManager* assets;
        SpriteRenderer* sprite_renderer;
        Camera2D* camera;

        PointerList<BaseGameObject>* game_objects;
        PointerList<BaseGameObject>* to_instantiate;

        PointerList<BaseGameObject>* physics_objects;
        PointerList<Collision::Result>* collisions;
    };

}
