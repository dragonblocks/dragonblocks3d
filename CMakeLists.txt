cmake_minimum_required(VERSION 3.0)

project(Dragonblocks)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("${PROJECT_SOURCE_DIR}/src/dragonblocks/")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/dragonblockslauncher/")
