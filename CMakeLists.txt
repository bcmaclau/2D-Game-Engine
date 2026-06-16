cmake_minimum_required(VERSION 3.20)
project(Engine2D VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Engine2D STATIC
    src/core/Game.cpp
    src/core/Window.cpp
    src/core/Time.cpp
    dependencies/glad/src/glad.c
    dependencies/stb/stb_image.cpp
)

target_include_directories(Engine2D PUBLIC
    include/
)

target_include_directories(Engine2D PRIVATE
    src/
    dependencies/glad/include/
    dependencies/stb/
)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)

target_link_libraries(Engine2D PUBLIC
    glfw
    glm::glm
)

add_subdirectory(testing)
