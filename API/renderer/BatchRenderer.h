#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "data_structures/PointerLinkedList.h"
#include "renderer/Shader.h"
#include "renderer/AssetManager.h"
#include "renderer/Camera2D.h"

namespace engine {

    namespace Component { class Sprite; }

    class BatchRenderer {
    public:
        static void init(unsigned int taid, int mw, int mh);
        static void shutdown();

        static void startBatch(Camera2D* camera);
        static void drawInOrder(PointerLinkedList<Component::Sprite>* go_render_order, PointerLinkedList<Component::Sprite>* ui_render_order);
        static void flushBatch();

    private:
        struct Vertex {
            float x, y;
            float u, v;
            float tex_index;
        };

        static const int MAX_SPRITES;
        static const int MAX_VERTICES;
        static const int MAX_INDICES;

        static Shader* shader;

        static unsigned int texture_array_id;
        static int max_tex_width, max_tex_height;
        static int num_layers;
        
        static Vertex* vertices;
        static unsigned int VAO, VBO, EBO;
        static int vertex_count;

        static const glm::vec4 quad_coords[4];

        static glm::vec2 camera_pos;

        BatchRenderer() {}
    };

}
