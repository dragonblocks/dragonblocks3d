cmake_minimum_required(VERSION 3.0)

project(Dragonblocks)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(dragonblocks SHARED
	src/animations.cpp
	src/async_mgr.cpp
	src/block.cpp
	src/block_def.cpp
	src/box_vertices.cpp
	src/camera.cpp
	src/chunk.cpp
	src/client.cpp
	src/entity.cpp
	src/face_dir.cpp
	src/game.cpp
	src/gl.cpp
	src/input_handler.cpp
	src/local_entity.cpp
	src/local_player.cpp
	src/map.cpp
	src/mapgen.cpp
	src/mesh.cpp
	src/render_engine.cpp
	src/scene.cpp
	src/shader_program.cpp
	src/texture.cpp
	src/tile_def.cpp
	src/window.cpp
)

target_link_libraries(dragonblocks
	GL
	GLEW
	glfw
)

target_include_directories(dragonblocks PUBLIC
	"${PROJECT_SOURCE_DIR}/lib/"
)

add_executable(dragonblocks.bin src/launcher/main.c)

target_link_libraries(dragonblocks.bin dl)
