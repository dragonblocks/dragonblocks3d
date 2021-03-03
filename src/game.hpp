#pragma once

#include "texture.hpp"

namespace dragonblocks
{
	class BlockDef;
	class Mapgen;

	class Game
	{
		public:
		BlockDef *air, *grass, *dirt, *stone, *snow;
		Mapgen *mapgen;
		Texture grass_texture, grass_side_texture, dirt_texture, stone_texture, snow_texture;

		Game(Mapgen *);
	};
}
