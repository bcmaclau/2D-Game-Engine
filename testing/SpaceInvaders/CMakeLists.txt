add_executable(SpaceInvaders main.cpp)
target_link_libraries(SpaceInvaders PRIVATE Engine2D)

get_target_property(ENGINE_DIR Engine2D SOURCE_DIR)

add_custom_target(SyncAssets ALL
    COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:SpaceInvaders>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SpaceInvaders>/assets
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ENGINE_DIR}/src/renderer/shaders
        $<TARGET_FILE_DIR:SpaceInvaders>/assets/shaders
)

add_dependencies(SpaceInvaders SyncAssets)
