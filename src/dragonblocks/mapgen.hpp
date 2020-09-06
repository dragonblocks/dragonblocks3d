#pragma once

#include "chunk.hpp"
#include "gl.hpp" 

namespace dragonblocks
{
	class BlockDef;
	
	class Mapgen
	{
		public:
		float grass_layer_middle = 0, grass_layer_range = 64;
		BlockDef *air_def, *stone_def, *dirt_def, *grass_def;
		
		Chunk::Data generate(const glm::ivec3 &) const;
	};
};
