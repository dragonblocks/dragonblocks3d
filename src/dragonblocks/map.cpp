#include <stdexcept>
#include "map.hpp"
#include "mapgen.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

ivec3 Map::getChunkPos(const vec3 &p)
{
	return floor(p / (float)DRAGONBLOCKS_CHUNK_SIZE);
}

ivec3 Map::getBlockPos(const ivec3 &p)
{
	return ((p % DRAGONBLOCKS_CHUNK_SIZE) + ivec3(DRAGONBLOCKS_CHUNK_SIZE)) % DRAGONBLOCKS_CHUNK_SIZE;
}

uint16_t Map::getChunkPosHash(const ivec3 &p)
{
	return (uint16_t)p.x + (uint16_t)p.y * DRAGONBLOCKS_MAP_SIZE + (uint16_t)p.z * DRAGONBLOCKS_MAP_SIZE * DRAGONBLOCKS_MAP_SIZE;
}

const Block *Map::getBlock(const glm::ivec3 &p)
{
	
	Chunk *chunk = getChunk(Map::getChunkPos(p));
	if (chunk)
		return chunk->getBlock(Map::getBlockPos(p));
	return nullptr;
}

void Map::setBlock(const glm::ivec3 &p, BlockDef *def)
{
	Chunk *chunk = getChunk(Map::getChunkPos(p));
	if (chunk)
		chunk->setBlock(Map::getBlockPos(p), def);
}

void Map::createChunk(const glm::ivec3 &p, const Chunk::Data &data)
{
	uint64_t poshash = Map::getChunkPosHash(p);
	
	if (chunks[poshash])
		return;

	chunks[poshash] = new Chunk(this, p, data, mesh_gen_mgr, scene);
}

void Map::createChunk(const glm::ivec3 &p)
{
	if (! chunks[Map::getChunkPosHash(p)])
		createChunk(p, mapgen->generate(p));
}	

Chunk *Map::getChunk(const glm::ivec3 &p)
{
	return chunks[Map::getChunkPosHash(p)];
}

void Map::clear()
{
	for (auto it = chunks.begin(); it != chunks.end(); it++)
		delete it->second;
	chunks.clear();
}

Map::Map(Mapgen *m, MeshGenMgr *mg, Scene *s) : mapgen(m), mesh_gen_mgr(mg), scene(s)
{
}

Map::~Map()
{
	clear();
}
