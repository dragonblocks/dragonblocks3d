#pragma once

#include <map>
#include "chunk.hpp"
#include "gl.hpp"

#define DRAGONBLOCKS_MAP_SIZE 1000

namespace dragonblocks
{
	class AsyncMgr;
	class BlockDef;
	class Block;
	class Mapgen;
	class Scene;
	class ShaderProgram;
	
	class Map
	{
		public:
		static glm::ivec3 getChunkPos(const glm::vec3 &);
		static glm::ivec3 getBlockPos(const glm::ivec3 &);
		static uint16_t getChunkPosHash(const glm::ivec3 &);
		
		const Block *getBlock(const glm::ivec3 &);
		const Block *getBlockRelativePos(Chunk *, const glm::ivec3 &);
		void setBlock(const glm::ivec3 &, BlockDef *);
		void createChunk(const glm::ivec3 &, const Chunk::Data &);
		void createChunk(const glm::ivec3 &);
		Chunk *getChunk(const glm::ivec3 &);
		void clear();
		
		Map(Mapgen *, AsyncMgr *, Scene *, ShaderProgram *);
		~Map();
		
		private:
		std::map<uint16_t, Chunk*> chunks;
		Mapgen *mapgen;
		AsyncMgr *async_mgr;
		Scene *scene;
		ShaderProgram *shader_program;
	};
}
