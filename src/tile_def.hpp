#pragma once

#include <vector>
#include "texture.hpp"

namespace dragonblocks
{
	class TileDef
	{
		public:
		std::vector<Texture> tiles;
		
		Texture get(int) const;
		int size() const;
		
		TileDef() = default;
		TileDef(const Texture &);
		TileDef(const std::vector<Texture> &);
	};
} 
