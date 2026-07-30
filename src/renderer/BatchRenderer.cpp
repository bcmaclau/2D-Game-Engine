#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/BatchRenderer.h"

#include "scene/component/Sprite.h"
#include <glm/ext/matrix_transform.hpp>

namespace engine {

    const int BatchRenderer::MAX_SPRITES = 300;
    const int BatchRenderer::MAX_VERTICES = MAX_SPRITES * 4;
    const int BatchRenderer::MAX_INDICES = MAX_SPRITES * 6;

    Shader* BatchRenderer::shader = nullptr;

    unsigned int BatchRenderer::texture_array_id = 0;
    int BatchRenderer::max_tex_width = 0;
    int BatchRenderer::max_tex_height = 0;
    int BatchRenderer::num_layers = 0;

    BatchRenderer::Vertex* BatchRenderer::vertices = nullptr;
    unsigned int BatchRenderer::VAO = 0;
    unsigned int BatchRenderer::VBO = 0;
    unsigned int BatchRenderer::EBO = 0;
    int BatchRenderer::vertex_count = 0;

    glm::vec2 BatchRenderer::camera_pos = { 0.0f, 0.0f };

    const glm::vec4 BatchRenderer::quad_coords[4] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        { 0.5f, -0.5f, 0.0f, 1.0f },
        { 0.5f, 0.5f, 0.0f, 1.0f },
        { -0.5f, 0.5f, 0.0f, 1.0f }
    };

    void BatchRenderer::init(unsigned int taid, int mw, int mh) {
        // data taken from asset manager
        texture_array_id = taid;
        max_tex_width = mw;
        max_tex_height = mh;

        // initialize the shader
        shader = new Shader();
        shader->init("assets/shaders/default.vert", "assets/shaders/default.frag");
        shader->use();
        shader->setInt("texture_array", 0);
        
        // allocate the max number of vertices
        vertices = (Vertex*)malloc(MAX_VERTICES * sizeof(Vertex));

        // initialize the VAO and VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // generate indices
        unsigned int indices[MAX_INDICES];
        int offset = 0;
        for (int i = 0; i < MAX_INDICES; i += 6) {
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset;
            offset += 4;
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void BatchRenderer::startBatch(Camera2D* camera) {
        camera_pos = camera->getPosition();

        glm::mat4 projection = camera->getProjectionMatrix();
        glm::mat4 view = camera->getViewMatrix();

        shader->use();
        shader->setMat4("projection", &projection);
        shader->setMat4("view", &view);

        vertex_count = 0;
    }

    void BatchRenderer::drawInOrder(PointerLinkedList<Component::Sprite>* go_render_order, PointerLinkedList<Component::Sprite>* ui_render_order) {
        if (vertex_count + 4 > MAX_VERTICES) {
            flushBatch();
            vertex_count = 0;
        }

        PLLNode<Component::Sprite>* current = go_render_order->getHead();
        bool on_go = true;

        while (current) {
            SpriteInfo* sprite_info = current->getData()->active_sprite;
            Component::Transform* transform = current->getData()->transform;

            glm::mat4 model = glm::mat4(1.0f);
            if (on_go) {
                model = glm::translate(model, glm::vec3(transform->getPosition().x, transform->getPosition().y, 0.0f));
            }
            else {
                model = glm::translate(model, glm::vec3(camera_pos.x + transform->getPosition().x, camera_pos.y + transform->getPosition().y, 0.0f));
            }
            model = glm::rotate(model, transform->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(sprite_info->dimensions.x, sprite_info->dimensions.y, 1.0f));

            glm::vec4 pos_0 = model * quad_coords[0];
            glm::vec4 pos_1 = model * quad_coords[1];
            glm::vec4 pos_2 = model * quad_coords[2];
            glm::vec4 pos_3 = model * quad_coords[3];

            vertices[vertex_count].x = pos_0.x;
            vertices[vertex_count].y = pos_0.y;
            vertices[vertex_count].u = sprite_info->u0;
            vertices[vertex_count].v = sprite_info->v0;
            vertices[vertex_count].tex_index = sprite_info->layer;

            vertices[vertex_count + 1].x = pos_1.x;
            vertices[vertex_count + 1].y = pos_1.y;
            vertices[vertex_count + 1].u = sprite_info->u1;
            vertices[vertex_count + 1].v = sprite_info->v0;
            vertices[vertex_count + 1].tex_index = sprite_info->layer;

            vertices[vertex_count + 2].x = pos_2.x;
            vertices[vertex_count + 2].y = pos_2.y;
            vertices[vertex_count + 2].u = sprite_info->u1;
            vertices[vertex_count + 2].v = sprite_info->v1;
            vertices[vertex_count + 2].tex_index = sprite_info->layer;

            vertices[vertex_count + 3].x = pos_3.x;
            vertices[vertex_count + 3].y = pos_3.y;
            vertices[vertex_count + 3].u = sprite_info->u0;
            vertices[vertex_count + 3].v = sprite_info->v1;
            vertices[vertex_count + 3].tex_index = sprite_info->layer;

            vertex_count += 4;
            current = current->getNext();
            if (current == nullptr && on_go) {
                on_go = false;
                current = ui_render_order->getHead();
            }
        }
        
        flushBatch();
    }

    void BatchRenderer::flushBatch() {
        if (vertex_count == 0) { return; }

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_count * sizeof(Vertex), vertices);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array_id);

        int index_count = (vertex_count / 4) * 6;
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    void BatchRenderer::shutdown() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        free(vertices);
    }

}
