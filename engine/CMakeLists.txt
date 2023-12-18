# Engine library
add_library(engine STATIC
    src/engine_source.cpp
    src/engine_systems.cpp
    src/ResourceManager.cpp
    src/Component.cpp
    src/SceneLayer.cpp
    include/engine_header.h
    include/engine_systems.h
    include/events.h
    include/GameObject.h
    include/Component.h
    include/ResourceManager.h
    ${CMAKE_SOURCE_DIR}/thirdparty/gfx/gfx.h
    ${CMAKE_SOURCE_DIR}/thirdparty/nlohmann/json.hpp
)

# Include directories for the engine library
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/thirdparty/gfx
    ${CMAKE_SOURCE_DIR}/thirdparty/nlohmann/
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    src/engine_source.cpp
    src/engine_systems.cpp
    include/engine_header.h
    include/engine_systems.h
)

add_dependencies(engine gfx)

# Link the engine library with gfx.lib
target_link_libraries(engine PUBLIC gfx)