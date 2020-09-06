#pragma once

#include "block.hpp"
#include "gl.hpp"
#include "mesh_gen_thread.hpp"

#define DRAGONBLOCKS_CHUNK_SIZE 16

namespace dragonblocks
{
	class Map;
	class Mesh;
	class Scene;
	
	class Chunk : public MeshGenThread::MeshGenerator
	{
		public:
		static void checkPos(const glm::ivec3 &);
		
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
		void updateMesh();
		
		Chunk(Map *, const glm::ivec3 &, const Data &, MeshGenThread *, Scene *);
		~Chunk();
		
		private:
		Map *map;
		Mesh *mesh = nullptr;
		MeshGenThread *mesh_gen_thread;
		Scene *scene;
		Data data;
		
		bool deleteMesh();
	};
}; 
