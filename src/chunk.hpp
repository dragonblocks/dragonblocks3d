#pragma once

#include "block.hpp"
#include "gl.hpp"
#include "async_mgr.hpp"

#define DRAGONBLOCKS_CHUNK_SIZE 16

namespace dragonblocks
{
	class Map;
	class Mesh;
	class Scene;
	class ShaderProgram;
	
	class Chunk : public AsyncMgr::ITask
	{
		public:
		static bool checkPos(const glm::ivec3 &);
		
		class Data
		{
			public:
			Block blocks[DRAGONBLOCKS_CHUNK_SIZE][DRAGONBLOCKS_CHUNK_SIZE][DRAGONBLOCKS_CHUNK_SIZE];
			Data() = default;
			Data(const Data &) = default;
		};
		
		glm::ivec3 pos;
		
		const Block *getBlock(const glm::ivec3 &) const;
		const Block *getBlockNoEx(const glm::ivec3 &) const;
		void setBlock(const glm::ivec3 &, const Block &);
		void setBlockNoEx(const glm::ivec3 &, const Block &);
		void addMeshUpdateTask();
		void addMeshUpdateTaskWithEdge();
		void updateMesh();
		void doAsyncTask();
		
		Chunk(Map *, const glm::ivec3 &, const Data &, AsyncMgr *, Scene *, ShaderProgram *);
		~Chunk();
		
		private:
		static void staticAfterAnimation(void *);
		
		Map *map;
		AsyncMgr *async_mgr;
		Scene *scene;
		ShaderProgram *shader_program;
		Mesh *mesh = nullptr;
		Data data;
		bool animation_finished = false;
		bool mesh_created = false;
		
		void afterAnimation();
	};
}; 
