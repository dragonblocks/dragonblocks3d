#include <iostream>
#include <stdexcept>
#include "animations.hpp"
#include "block_def.hpp"
#include "box_vertices.hpp"
#include "chunk.hpp"
#include "face_dir.hpp"
#include "map.hpp"
#include "mesh.hpp"
#include "texture.hpp"

#define SIZE DRAGONBLOCKS_CHUNK_SIZE

using namespace std;
using namespace glm;
using namespace dragonblocks;

bool Chunk::checkPos(const ivec3 &pos)
{
	return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.x < SIZE && pos.y < SIZE && pos.z < SIZE;
}

const Block *Chunk::getBlock(const ivec3 &pos) const
{
	const Block *b = getBlockNoEx(pos);
	if (! b) {
		throw out_of_range("Block position out of range");
	}
	return b;
}

const Block *Chunk::getBlockNoEx(const ivec3 &pos) const
{
	return Chunk::checkPos(pos) ? &data.blocks[pos.x][pos.y][pos.z] : nullptr;
}

void Chunk::setBlock(const ivec3 &pos, const Block &block)
{
	if (! Chunk::checkPos(pos)) {
		throw out_of_range("Block position out of range");
	}
	data.blocks[pos.x][pos.y][pos.z] = block;
}

void Chunk::setBlockNoEx(const ivec3 &pos, const Block &block)
{
	try {
		setBlock(pos, block);
	} catch (out_of_range &) {
	}
}

void Chunk::addMeshUpdateTask()
{
	async_mgr->addTask(this);
}

void Chunk::addMeshUpdateTaskWithEdge()
{
	addMeshUpdateTask();
	for (int i = 0; i < 6; i++) {
		if (Chunk *neighbor = map->getChunk(pos + face_dir[i])) {
			neighbor->addMeshUpdateTask();
		}
	}
}

void Chunk::updateMesh()
{
	cout << "Update Chunk Mesh at " << pos.x << " " << pos.y << " " << pos.z << endl;

	if (mesh_created && ! animation_finished)
		return;

	bool mesh_created_before = mesh_created;
	mesh_created = true;

	vector<GLfloat> vertices;
	vector<Texture> textures;
	bool any_drawable_block = false;

	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			for (int z = 0; z < SIZE; z++) {
				Block *block = &data.blocks[x][y][z];
				BlockDef *def = block->getDef();
				if (! def->drawable)
					continue;
				ivec3 bpos(x, y, z);
				vec3 pos_from_mesh_origin = vec3(bpos) - vec3(SIZE / 2 + 0.5);
				for (int facenr = 0; facenr < 6; facenr++) {
					ivec3 npos = bpos + face_dir[facenr];
					const Block *neighbor_own, *neighbor;
					neighbor_own = neighbor = getBlockNoEx(npos);
					if (! neighbor)
						neighbor = map->getBlock(pos * SIZE + npos);
					if (neighbor && ! neighbor->getDef()->drawable)
						any_drawable_block = true;
					if (! mesh_created_before)
						neighbor = neighbor_own;
					if (! mesh_created_before && ! neighbor || neighbor && ! neighbor->getDef()->drawable) {
						textures.push_back(def->tile_def.get(facenr));
						for (int vertex_index = 0; vertex_index < 6; vertex_index++) {
							for (int attribute_index = 0; attribute_index < 5; attribute_index++) {
								GLdouble value = box_vertices[facenr][vertex_index][attribute_index];
								switch (attribute_index) {
									case 0:
									value += pos_from_mesh_origin.x;
									break;
									case 1:
									value += pos_from_mesh_origin.y;
									break;
									case 2:
									value += pos_from_mesh_origin.z;
									break;
								}
								vertices.push_back(value);
							}
						}
					}
				}
			}
		}
	}

	if (! any_drawable_block) {
		if (! mesh_created_before) {
			afterAnimation();
		} else if (mesh) {
			mesh->die();
			mesh = nullptr;
		}
		return;
	}

	Mesh *oldmesh = mesh;

	mesh = new Mesh(scene, shader_program, &vertices[0], vertices.size());
	mesh->pos = pos * SIZE + SIZE / 2;
	mesh->minp = vec3(- SIZE / 2);
	mesh->maxp = vec3(+ SIZE / 2);
	mesh->textures = textures;
	mesh->vertices_per_texture = 6;
	if (! mesh_created_before) {
		mesh->animation = new GrowAnimation(0.25, Chunk::staticAfterAnimation, this);
	}

	if (oldmesh) {
		oldmesh->die();
	}
}

void Chunk::doAsyncTask()
{
	updateMesh();
}

Chunk::Chunk(Map *m, const ivec3 &p, const Data &d, AsyncMgr *a, Scene *s, ShaderProgram *sh) : map(m), data(d), pos(p), async_mgr(a), scene(s), shader_program(sh)
{
	addMeshUpdateTask();
}

Chunk::~Chunk()
{
	if (mesh) {
		mesh->die();
	}
}

void Chunk::staticAfterAnimation(void *chunk)
{
	if (chunk) {
		((Chunk *)chunk)->afterAnimation();
	}
}

void Chunk::afterAnimation()
{
	animation_finished = true;
	addMeshUpdateTaskWithEdge();
}
