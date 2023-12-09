cmake_minimum_required(VERSION 3.10)
project(SAGE)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add subdirectories for engine and editor
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(thirdparty/gfx)
