add_executable(Breakout main.cpp)

target_link_libraries(Breakout PRIVATE Engine2D)

add_custom_command(TARGET Breakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Breakout>/assets
)

add_custom_command(TARGET Breakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/renderer/shaders $<TARGET_FILE_DIR:Breakout>/assets/shaders
)
