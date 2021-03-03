#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp> 

//#define CHECKERR dragonblocks::checkGLError(__FILE__, __LINE__);
#define CHECKERR

namespace dragonblocks
{
	GLenum checkGLError(const char *file, int line);
}
