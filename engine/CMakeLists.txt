# Engine library
add_library(engine STATIC
    src/Engine.cpp
    src/Entity.cpp
    src/Events.cpp
    src/Systems.cpp
    src/Component.cpp
    src/Scene.cpp
    src/Game.cpp
    src/Render.cpp
    src/Debug.cpp
    include/Engine.h
    include/Systems.h
    include/Events.h
    include/Entity.h
    include/Component.h
    include/Scene.h
    include/Game.h
    include/Render.h
    include/Debug.h
    ${CMAKE_SOURCE_DIR}/thirdparty/gfx/gfx.h
    ${CMAKE_SOURCE_DIR}/thirdparty/nlohmann/json.hpp
)

# Include directories for the engine library
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/thirdparty/gfx
    ${CMAKE_SOURCE_DIR}/thirdparty/nlohmann/
)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES )

add_dependencies(engine gfx)

# Link the engine library with gfx.lib
target_link_libraries(engine PUBLIC gfx)