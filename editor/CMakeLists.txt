# Application
add_executable(editor
    src/main.cpp
)

set(GFX_DXC_PATH ${CMAKE_SOURCE_DIR}/thirdparty/gfx/third_party/dxc)
set(GFX_PIX_PATH ${CMAKE_SOURCE_DIR}/thirdparty/gfx/third_party/WinPixEventRuntime)

add_custom_command(
    TARGET editor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${GFX_DXC_PATH}/bin/x64/dxil.dll
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/dxil.dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${GFX_DXC_PATH}/bin/x64/dxcompiler.dll
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/dxcompiler.dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${GFX_PIX_PATH}/bin/x64/WinPixEventRuntime.dll
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/WinPixEventRuntime.dll
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/editor/src/scene1.json
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/scene1.json
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/editor/src/triangle.vert
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/triangle.vert
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/editor/src/triangle.frag
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/triangle.frag
)

# Link the application with the engine library

add_dependencies(editor engine)

target_link_libraries(editor
    PRIVATE engine
)

target_include_directories(editor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)
