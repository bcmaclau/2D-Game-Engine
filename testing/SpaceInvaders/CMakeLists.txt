add_executable(SpaceInvaders main.cpp)

target_link_libraries(SpaceInvaders PRIVATE Engine2D)

add_custom_command(TARGET SpaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:SpaceInvaders>/assets
)

add_custom_command(TARGET SpaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/renderer/shaders $<TARGET_FILE_DIR:SpaceInvaders>/assets/shaders
)
