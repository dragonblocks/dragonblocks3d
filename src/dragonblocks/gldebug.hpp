#pragma once

#include "gl.hpp"

#define glCheckError() glCheckError_(__FILE__, __LINE__)
#define CHECKERR glCheckError();

GLenum glCheckError_(const char *file, int line);

