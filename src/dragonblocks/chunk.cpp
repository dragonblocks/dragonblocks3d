#include <stdexcept>
#include "block_def.hpp" 
#include "chunk.hpp" 
#include "cube.hpp"
#include "face_dir.hpp" 
#include "map.hpp" 
#include "mesh.hpp" 
#include "texture.hpp" 

#define SIZE DRAGONBLOCKS_CHUNK_SIZE

using namespace std;
using namespace glm;
using namespace dragonblocks;

void Chunk::checkPos(const ivec3 &pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= SIZE || pos.y >= SIZE || pos.z >= SIZE)
		throw out_of_range("Block position out of range");
}

const Block *Chunk::getBlock(const ivec3 &pos) const
{
	Chunk::checkPos(pos);
	return &data.blocks[pos.x][pos.y][pos.z];	
}

const Block *Chunk::getBlockNoEx(const ivec3 &pos) const
{
	try {
		return getBlock(pos);
	} catch (std::out_of_range &) {
		return nullptr;
	}
}

void Chunk::setBlock(const ivec3 &pos, const Block &block)
{
	Chunk::checkPos(pos);
	data.blocks[pos.x][pos.y][pos.z] = block;
}

void Chunk::setBlockNoEx(const ivec3 &pos, const Block &block)
{
	try {
		setBlock(pos, block);
	} catch (std::out_of_range &) {
	}
}

void Chunk::updateMesh()
{
	std::vector<GLfloat> vertices;
	std::vector<Texture> textures;
	
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			for (int z = 0; z < SIZE; z++) {
				Block *block = &data.blocks[x][y][z];
				BlockDef *def = block->getDef();
				if (! def->drawable)
					continue;
				vec3 pos(x, y, z);
				vec3 pos_from_mesh_origin = pos - vec3(SIZE / 2 + 0.5);
				for (int facenr = 0; facenr < 6; facenr++) {
					const Block *neighbor = map->getBlockRelativePos(this, pos + (vec3)face_dir[facenr]);
					if (neighbor && ! neighbor->getDef()->drawable) {
						textures.push_back(def->tiles[facenr]);
						for (int vertex_index = 0; vertex_index < 6; vertex_index++) {
							for (int attribute_index = 0; attribute_index < 5; attribute_index++) {
								int index = facenr * 6 * 5 + vertex_index * 5 + attribute_index;
								GLdouble value = cube[index];
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

	bool is_new = ! deleteMesh();
	
	if (textures.size() == 0) {
		return;
	}

	mesh = new Mesh(scene);
	mesh->pos = pos * SIZE + SIZE / 2;
	mesh->size = vec3(1.0);
	mesh->configureVertexObjects(&vertices[0], vertices.size() * sizeof(GLfloat));
	mesh->textures = textures;
	mesh->vertices_per_texture = 6;
	if (is_new)
		mesh->effect = Mesh::Effect::Type::FLYIN;
	mesh->addToScene();
}

void Chunk::addMeshUpdateTask()
{
	mesh_gen_thread->addTask(this);
}

bool Chunk::deleteMesh()
{
	if (mesh) {
		mesh->removeFromScene();
		delete mesh;
		mesh = nullptr;
		return true;
	}
	return false;
}

Chunk::Chunk(Map *m, const glm::ivec3 &p, const Data &d, MeshGenThread *mgt, Scene *s) : map(m), data(d), pos(p), mesh_gen_thread(mgt), scene(s)
{
	addMeshUpdateTask();
}

Chunk::~Chunk()
{
	deleteMesh();
}
