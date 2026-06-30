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
            obj->init(assets, game_objects.size(), &to_instantiate, &physics_objects);
            game_objects.push_back(obj);
            return obj;
        }
        void destroy(BaseGameObject* obj);

    protected:
        // user implemented functions
        virtual void onInit() {}
        virtual void onUpdate(float dt) {}
        virtual void onFixedUpdate() {}
        virtual void onShutdown() {}

    private:
        void init(AssetManager* a, int screen_width, int screen_height);
        void update(float dt);
        void fixedUpdate();
        void draw();
        void endFrame();
        void shutdown();

        void dynamicInstantiate(BaseGameObject* obj);

        bool swap_scene;
        BaseScene* new_scene;
        bool end_game;

        AssetManager* assets;
        SpriteRenderer* sprite_renderer;
        Camera2D* camera;

        std::vector<BaseGameObject*> game_objects;
        std::vector<BaseGameObject*> to_instantiate;

        std::vector<BaseGameObject*> physics_objects;
        std::vector<Collision::Result*> collisions;
    };

}
