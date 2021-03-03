#pragma once

#include <string>
#include "gl.hpp"
#include "tile_def.hpp"

namespace dragonblocks
{
	class BlockDef
	{
		public:		
		std::string name;
		TileDef tile_def;
		bool drawable = true;
		
		BlockDef(const std::string &);
		BlockDef(const std::string &, const TileDef &);
	};
} 
