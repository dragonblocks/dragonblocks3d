#pragma once

#include "gl.hpp"

namespace dragonblocks
{
	class BlockDef;
	class Block
	{
		public:		
		BlockDef *getDef() const;
		
		Block() = default;
		Block(const Block &) = default;
		Block(BlockDef *);
		
		private:
		BlockDef *def = nullptr;
	};
}
 
