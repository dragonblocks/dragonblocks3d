#include <iostream>
#include <glm/gtc/noise.hpp>
#include "mapgen.hpp" 

using namespace glm;
using namespace dragonblocks;

Chunk::Data Mapgen::generate(const ivec3 &chunkp) const
{
	Chunk::Data data;
	vec3 minp = chunkp * ivec3(DRAGONBLOCKS_CHUNK_SIZE);
	vec3 maxp = minp + vec3(DRAGONBLOCKS_CHUNK_SIZE);
	int minx = minp.x, miny = minp.y, minz = minp.z, maxx = maxp.x, maxy = maxp.y, maxz = maxp.z;
	for (int x = minx; x < maxx; x++) {
		int rx = x - minx;
		for (int z = minz; z < maxz; z++) {
			int rz = z - minz;
			int grass_layer = grass_layer_middle + grass_layer_range * perlin(vec2((float)x / 64, (float)z / 64));
			for (int y = miny; y < maxy; y++) {
				int ry = y - miny;
				BlockDef *blockdef;
				if (y < grass_layer - 4)
					blockdef = stone_def;
				else if (y < grass_layer - 1)
					blockdef = dirt_def;
				else if (y < grass_layer)
					blockdef = grass_def;
				else
					blockdef = air_def;
				data.blocks[rx][ry][rz] = blockdef;
			}
		}
	}
	return data;
}
