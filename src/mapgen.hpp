#pragma once

#include "chunk.hpp"
#include "gl.hpp"

namespace dragonblocks
{
	class BlockDef;

	class Mapgen
	{
		public:
		BlockDef *air_def, *stone_def, *dirt_def, *grass_def, *snow_def;

		Chunk::Data generate(const glm::ivec3 &) const;
	};
};
