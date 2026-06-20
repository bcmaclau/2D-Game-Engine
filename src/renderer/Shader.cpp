#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "engine/renderer/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace engine {

    Shader::Shader() {}
    Shader::~Shader() {
        if (id) {
            glDeleteProgram(id);
        }
    }

    bool Shader::init(const char* vertex_path, const char* fragment_path) {
        std::string vertex_code, fragment_code;
        std::ifstream v_shader_file, f_shader_file;

        v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            v_shader_file.open(vertex_path);
            f_shader_file.open(fragment_path);
            std::stringstream v_shader_stream, f_shader_stream;

            v_shader_stream << v_shader_file.rdbuf();
            f_shader_stream << f_shader_file.rdbuf();

            v_shader_file.close();
            f_shader_file.close();

            vertex_code = v_shader_stream.str();
            fragment_code = f_shader_stream.str();
        } 
        catch (std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return false;
        }
        const char* v_shader_code = vertex_code.c_str();
        const char* f_shader_code = fragment_code.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &v_shader_code, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &f_shader_code, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return false;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return true;
    }

    void Shader::setMat4(const char* name, glm::mat4* mat) {
        glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(*mat));
    }

    void Shader::use() {
        glUseProgram(id);
    }

    void Shader::shutdown() {
        if (id)  {
            glUseProgram(0);
            glDeleteProgram(id);
            id = 0;
        }
    }

}
