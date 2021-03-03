#include <iostream>
#include <glm/gtc/noise.hpp>
#include "map.hpp"
#include "mapgen.hpp"

using namespace glm;
using namespace dragonblocks;

Chunk::Data Mapgen::generate(const ivec3 &chunkp) const
{
	int map_size = DRAGONBLOCKS_CHUNK_SIZE * DRAGONBLOCKS_MAP_SIZE;

	Chunk::Data data;
	vec3 minp = chunkp * ivec3(DRAGONBLOCKS_CHUNK_SIZE);
	vec3 maxp = minp + vec3(DRAGONBLOCKS_CHUNK_SIZE);
	int minx = minp.x, miny = minp.y, minz = minp.z, maxx = maxp.x, maxy = maxp.y, maxz = maxp.z;
	for (int x = minx; x < maxx; x++) {
		int rx = x - minx;
		int ux = x + map_size;

		for (int z = minz; z < maxz; z++) {
			int rz = z - minz;
			int uz = z + map_size;
			int height = perlin(vec2((float)ux / 200, (float)uz / 200)) * 25 + 100;

			bool is_mountain = false;
			float mountain_factor = pow((perlin(vec2((float)ux / 1000.0f, (float)uz / 1000.0f)) - 0.3f) * 5.0f, 1.0f);
			if (mountain_factor > 0) {
				height = pow(height * pow(((perlin(vec2((float)ux / 50.0f, (float)uz / 50.0f)) + 1.0f) * 200.0f + 100.0f), mountain_factor), 1.0f / (mountain_factor + 1.0f));
				is_mountain = true;
			}

			BlockDef *blockdef = nullptr;

			for (int y = maxy - 1; y >= miny; y--) {
				int ry = y - miny;

				int by = y + 100;

				BlockDef *new_blockdef = air_def;

				int diff = by - height;

				if (diff < -5)
					new_blockdef = stone_def;
				else if (diff < -1)
					new_blockdef = is_mountain ? stone_def : dirt_def;
				else if (diff < 0)
					new_blockdef = is_mountain ? stone_def : grass_def;
				else if (diff < 1)
					new_blockdef = is_mountain && by > 150 ? snow_def : air_def;

				if (new_blockdef == dirt_def && (! blockdef || blockdef == air_def))
					new_blockdef = grass_def;

				data.blocks[rx][ry][rz] = new_blockdef;
			}
		}
	}
	return data;
}
