#pragma once

#include <string>
#include "gl.hpp"

namespace dragonblocks
{
	class Texture
	{
		public:
		static bool mipmap;
		static bool bilinear_filter;
		
		static void initArgs();
		
		void bind() const;
		void load(const std::string &);
		Texture() = default;
		Texture(const Texture &) = default;
		
		private:
		static GLenum min_filter, mag_filter;
		
		GLuint id;
	};
}
