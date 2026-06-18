add_executable(TestGame main.cpp)

target_link_libraries(TestGame PRIVATE Engine2D)

add_custom_command(TARGET TestGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TestGame>/assets
)
