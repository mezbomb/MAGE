# Application
add_executable(editor
    src/main.cpp
)

# Link the application with the engine library
target_link_libraries(editor
    PRIVATE engine
)

target_include_directories(editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)
