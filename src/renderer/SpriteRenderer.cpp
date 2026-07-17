#include <glad/glad.h>

#include "renderer/SpriteRenderer.h"

#include <glm/ext/matrix_transform.hpp>

namespace engine {

    bool SpriteRenderer::init() {
        if (!shader.init("assets/shaders/default.vert", "assets/shaders/default.frag")) { return false; }

        float vertices[] = {
            // 2 normal coords, 2 tex coords
            -1.0f, 1.0f, 0.0f, 1.0f, // top left
            -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
            1.0f, 1.0f, 1.0f, 1.0f, // top right
            1.0f, -1.0f, 1.0f, 0.0f // bottom right
        };

        // draw in a quad with 2 counter-clockwise triangles
        unsigned int indices[] = {
            0, 1, 2,
            2, 1, 3
        };

        glGenVertexArrays(1, &VAO);
        if (!VAO) { return false; }
        glGenBuffers(1, &VBO);
        if (!VBO) { return false; }
        glGenBuffers(1, &EBO);
        if (!EBO) { return false; }

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        return true;
    }

    void SpriteRenderer::beginFrame(Camera2D* camera) {
        shader.use();

        glm::mat4 projection = camera->getProjectionMatrix();
        shader.setMat4("projection", &projection);
        glm::mat4 view = camera->getViewMatrix();
        shader.setMat4("view", &view);

        glBindVertexArray(VAO);
    }

    void SpriteRenderer::drawSprite(Component::Sprite* sprite, Component::Transform* transform) {
        glm::vec2 pos = glm::vec2(transform->getPosition().x, transform->getPosition().y);
        glm::vec2 dim = glm::vec2(sprite->active_sprite->dimensions.x, sprite->active_sprite->dimensions.y);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));
        model = glm::rotate(model, glm::radians(transform->getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(dim / 2.0f, 1.0f));

        float min_tex_x = sprite->active_sprite->current_frame * sprite->active_sprite->frame_width;
        float max_tex_x = min_tex_x + sprite->active_sprite->frame_width;

        float vertices[] = {
            // 2 normal coords, 2 tex coords
            -1.0f, 1.0f, min_tex_x, 1.0f, // top left
            -1.0f, -1.0f, min_tex_x, 0.0f, // bottom left
            1.0f, 1.0f, max_tex_x, 1.0f, // top right
            1.0f, -1.0f, max_tex_x, 0.0f // bottom right
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        shader.setMat4("model", &model);
        sprite->active_sprite->texture->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void SpriteRenderer::drawUI(Component::Sprite* sprite, Component::Transform* transform) {
        glm::vec2 pos = glm::vec2(camera_pos.x + transform->getPosition().x, camera_pos.y + transform->getPosition().y);
        glm::vec2 dim = glm::vec2(sprite->active_sprite->dimensions.x, sprite->active_sprite->dimensions.y);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));
        model = glm::rotate(model, glm::radians(transform->getRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(dim / 2.0f, 1.0f));

        float min_tex_x = sprite->active_sprite->current_frame * sprite->active_sprite->frame_width;
        float max_tex_x = min_tex_x + sprite->active_sprite->frame_width;

        float vertices[] = {
            // 2 normal coords, 2 tex coords
            -1.0f, 1.0f, min_tex_x, 1.0f, // top left
            -1.0f, -1.0f, min_tex_x, 0.0f, // bottom left
            1.0f, 1.0f, max_tex_x, 1.0f, // top right
            1.0f, -1.0f, max_tex_x, 0.0f // bottom right
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        shader.setMat4("model", &model);
        sprite->active_sprite->texture->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void SpriteRenderer::endFrame() {}

    void SpriteRenderer::shutdown() {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        shader.shutdown();
    }

}
