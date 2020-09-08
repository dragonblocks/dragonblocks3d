cmake_minimum_required(VERSION 3.0)

set(srcpath "${PROJECT_SOURCE_DIR}/src/dragonblocks")

add_library(dragonblocks SHARED
	block.cpp
	block_def.cpp
	camera.cpp
	chunk.cpp
	client.cpp
	core.cpp
	cube.cpp
	face_dir.cpp
	game.cpp
	gldebug.cpp
	input_handler.cpp
	log.cpp
	mainmenu.cpp
	map.cpp
	mapgen.cpp
	mesh.cpp
	mesh_gen_mgr.cpp
	render_engine.cpp
	scene.cpp
	server.cpp
	shader_program.cpp
	texture.cpp
	window.cpp
	world.cpp
)

target_link_libraries(dragonblocks
	GL
	GLEW
	glfw
)

target_include_directories(dragonblocks PUBLIC
	"${PROJECT_SOURCE_DIR}/lib/"
	"${PROJECT_SOURCE_DIR}/src/"
)

