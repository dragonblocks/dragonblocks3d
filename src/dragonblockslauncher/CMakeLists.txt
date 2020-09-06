cmake_minimum_required(VERSION 3.0)

add_executable(dragonblockslauncher
	launcher.cpp
	main.cpp
)

target_link_libraries(dragonblockslauncher dl)

target_include_directories(dragonblockslauncher PUBLIC
	"${PROJECT_SOURCE_DIR}/lib/"
	"${PROJECT_SOURCE_DIR}/src/"
)
