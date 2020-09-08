#pragma once

#include "gl.hpp"

#define CHECKERR dragonblocks::checkGLError(__FILE__, __LINE__);

namespace dragonblocks
{
	GLenum checkGLError(const char *file, int line);
}
