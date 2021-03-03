#include "tile_def.hpp"

using namespace std;
using namespace dragonblocks;

Texture TileDef::get(int i) const
{
	return tiles[i];
}

int TileDef::size() const
{
	return tiles.size();
}

TileDef::TileDef(const vector<Texture> &t) : tiles(t)
{
	int s = size();
	for (int i = 0; s < 6; i += s) {
		for (int j = 0; j < i && j + i < 6; j++) {
			tiles[i + j] = tiles[j];
		}
	} 
}

TileDef::TileDef(const Texture &t) : TileDef({t, t, t, t, t, t})
{
}


