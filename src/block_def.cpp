#include "block_def.hpp"

using namespace std;
using namespace dragonblocks;

BlockDef::BlockDef(const string &n, const TileDef &t) : name(n), tile_def(t)
{
	if (tile_def.size() == 0) {
		drawable = false;
	}
}

BlockDef::BlockDef(const string &n) : BlockDef(n, TileDef())
{
}
