#include <stdexcept>
#include "face_dir.hpp"
#include "map.hpp"
#include "mapgen.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

ivec3 Map::getChunkPos(const vec3 &p)
{
	return floor(p / 16.0F);
}

ivec3 Map::getBlockPos(const ivec3 &p)
{
	return ((p % 16) + ivec3(16)) % 16;
}

uint16_t Map::getChunkPosHash(const ivec3 &p)
{
	return (uint16_t)p.x + (uint16_t)p.y * 1000 + (uint16_t)p.z * 1000000;
}

const Block *Map::getBlock(const glm::ivec3 &p)
{
	
	Chunk *chunk = getChunk(Map::getChunkPos(p));
	if (chunk)
		return chunk->getBlock(Map::getBlockPos(p));
	return nullptr;
}

const Block *Map::getBlockRelativePos(Chunk *chunk, const glm::ivec3 &p)
{
	const Block *b = nullptr;
	try {
		b = chunk->getBlock(p);
	} catch (std::out_of_range &) {
		b = getBlock(chunk->pos * 16 + p);
	}
	return b;
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

	chunks[poshash] = new Chunk(this, p, data, mesh_gen_thread, scene);
	
	for (int i = 0; i < 6; i++) {
		if (Chunk *neighbor = getChunk(p + face_dir[i]))
			neighbor->addMeshUpdateTask();
	}
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

Map::Map(Mapgen *m, MeshGenThread *mgt, Scene *s) : mapgen(m), mesh_gen_thread(mgt), scene(s)
{
}

Map::~Map()
{
	clear();
}
