#include "block.hpp" 

using namespace dragonblocks;

BlockDef *Block::getDef() const
{
	return def;
}

Block::Block(BlockDef *d) : def(d)
{
}
