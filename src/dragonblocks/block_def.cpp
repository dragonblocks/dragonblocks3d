#include "block_def.hpp"

using namespace std;
using namespace dragonblocks;

BlockDef::BlockDef(const string &n, const vector<Texture> &t) : name(n), tiles(t)
{
	int s = tiles.size();
	if (s == 0) {
		drawable = false;
	} else {
		for (int i = 0; s < 6; i += s) {
			for (int j = 0; j < i && j + i < 6; j++) {
				tiles[i + j] = tiles[j];
			}
		}
	}
}

BlockDef::BlockDef(const string &n, const Texture &t) : BlockDef(n, {t, t, t, t, t, t})
{
}

BlockDef::BlockDef(const string &n) : BlockDef(n, vector<Texture>())
{
}
