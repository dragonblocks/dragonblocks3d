#pragma once

#include <string>
#include <vector>
#include "gl.hpp"
#include "texture.hpp"

namespace dragonblocks
{
	class BlockDef
	{
		public:		
		std::string name;
		std::vector<Texture> tiles;
		bool drawable = true;
		
		BlockDef(const std::string &);
		BlockDef(const std::string &, const Texture &);
		BlockDef(const std::string &, const std::vector<Texture> &);
	};
} 
