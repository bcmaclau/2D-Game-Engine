cmake_minimum_required(VERSION 3.20)
project(Engine2D VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Engine2D STATIC
    src/core/Game.cpp
    src/core/Window.cpp
    src/core/Time.cpp
    src/core/Paths.cpp
    src/renderer/Shader.cpp
    src/renderer/Texture.cpp
    src/renderer/Camera2D.cpp
    src/renderer/SpriteRenderer.cpp
    src/renderer/AssetManager.cpp
    src/input/Input.cpp
    src/scene/BaseGameObject.cpp
    src/scene/BaseScene.cpp
    src/scene/Components.cpp
    src/physics/Collision.cpp
    src/math/Vector.cpp
    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)

target_include_directories(Engine2D PUBLIC
    include/
)

target_include_directories(Engine2D PRIVATE
    src/
    API/
    dependencies/glad/include/
    dependencies/
)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)

target_link_libraries(Engine2D PUBLIC
    glfw
    glm::glm
)

add_subdirectory(testing)
