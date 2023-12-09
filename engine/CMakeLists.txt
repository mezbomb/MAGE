# Engine library
add_library(engine STATIC
    src/engine_source.cpp
    src/engine_systems.cpp
    include/engine_header.h
    include/engine_systems.h
     ${CMAKE_SOURCE_DIR}/thirdparty/gfx/gfx.h
)

# Include directories for the engine library
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/thirdparty/gfx
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