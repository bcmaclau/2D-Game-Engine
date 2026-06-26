#pragma once

#include <glm/glm.hpp>

namespace engine {

    class Shader {
    public:
        Shader() {}
        ~Shader() {}

        bool init(const char* vertex_path, const char* fragment_path);
        void setMat4(const char* name, glm::mat4* mat);
        void use();
        void shutdown();

    private:
        unsigned int id;
    };

}