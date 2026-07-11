add_executable(Game main.cpp)

target_link_libraries(Game PRIVATE Engine2D)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Game>/assets
)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer/shaders $<TARGET_FILE_DIR:Game>/assets/shaders
)
