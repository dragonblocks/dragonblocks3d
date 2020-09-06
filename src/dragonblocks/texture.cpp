#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "log.hpp"
#include "texture.hpp"

using namespace std;
using namespace dragonblocks;

bool Texture::mipmap;
bool Texture::bilinear_filter;
GLenum Texture::min_filter, Texture::mag_filter;

void Texture::initArgs()
{
	min_filter = mag_filter = bilinear_filter ? GL_LINEAR : GL_NEAREST;
	if (mipmap) {
		if (min_filter == GL_NEAREST) {
			min_filter = GL_NEAREST_MIPMAP_NEAREST;
		} else {
			min_filter = GL_LINEAR_MIPMAP_NEAREST;
		}
	}
	stbi_set_flip_vertically_on_load(true);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::load(const string &path)
{
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (! data)
		throw runtime_error("Failed to load texture " + path);
	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture::min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Texture::mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (Texture::mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	log("Loaded texture " + path);
}

