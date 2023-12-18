cmake_minimum_required(VERSION 3.10)
project(SAGE)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Set the working directory for the project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Add subdirectories for engine and editor
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(thirdparty/gfx)
