#include "cube.hpp"

GLfloat dragonblocks::cube[DRAGONBLOCKS_CUBE_VERTEX_COUNT] = {
//  x     y     z      s     t
	-0.5, -0.5, -0.5,  +0.0, +0.0,
	+0.5, -0.5, -0.5,  +1.0, +0.0,
	+0.5, +0.5, -0.5,  +1.0, +1.0,
	+0.5, +0.5, -0.5,  +1.0, +1.0,
	-0.5, +0.5, -0.5,  +0.0, +1.0,
	-0.5, -0.5, -0.5,  +0.0, +0.0,

	-0.5, -0.5, +0.5,  +0.0, +0.0, 
	+0.5, +0.5, +0.5,  +1.0, +1.0,
	+0.5, -0.5, +0.5,  +1.0, +0.0,
	+0.5, +0.5, +0.5,  +1.0, +1.0,
	-0.5, -0.5, +0.5,  +0.0, +0.0,
	-0.5, +0.5, +0.5,  +0.0, +1.0,

	-0.5, +0.5, +0.5,  +1.0, +1.0,
	-0.5, -0.5, -0.5,  +0.0, +0.0,
	-0.5, +0.5, -0.5,  +0.0, +1.0,
	-0.5, -0.5, -0.5,  +0.0, +0.0,
	-0.5, +0.5, +0.5,  +1.0, +1.0,
	-0.5, -0.5, +0.5,  +1.0, +0.0,

	+0.5, +0.5, +0.5,  +1.0, +1.0, 
	+0.5, +0.5, -0.5,  +0.0, +1.0,
	+0.5, -0.5, -0.5,  +0.0, +0.0,
	+0.5, -0.5, -0.5,  +0.0, +0.0,
	+0.5, -0.5, +0.5,  +1.0, +0.0,
	+0.5, +0.5, +0.5,  +1.0, +1.0,

	-0.5, -0.5, -0.5,  +0.0, +1.0,
	+0.5, -0.5, -0.5,  +1.0, +1.0,
	+0.5, -0.5, +0.5,  +1.0, +0.0,
	+0.5, -0.5, +0.5,  +1.0, +0.0,
	-0.5, -0.5, +0.5,  +0.0, +0.0,
	-0.5, -0.5, -0.5,  +0.0, +1.0,

	-0.5, +0.5, -0.5,  +0.0, +1.0,
	+0.5, +0.5, -0.5,  +1.0, +1.0,
	+0.5, +0.5, +0.5,  +1.0, +0.0,
	+0.5, +0.5, +0.5,  +1.0, +0.0,
	-0.5, +0.5, +0.5,  +0.0, +0.0,
	-0.5, +0.5, -0.5,  +0.0, +1.0,
};
