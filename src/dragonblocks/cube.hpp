#pragma once

#include "gl.hpp"

#define DRAGONBLOCKS_CUBE_VERTEX_COUNT 5 * 6 * 6 // 5 floats per vertex, 6 vertices per face, 6 faces

namespace dragonblocks
{
	extern GLfloat cube[DRAGONBLOCKS_CUBE_VERTEX_COUNT];		
} 
