# Engine library
add_library(engine STATIC
    src/engine_source.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
