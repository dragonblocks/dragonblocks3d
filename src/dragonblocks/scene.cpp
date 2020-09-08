#include "mesh.hpp"
#include "scene.hpp"

using namespace std;
using namespace dragonblocks;

void Scene::add(Mesh *m)
{
	meshes.insert(m);
}

void Scene::remove(Mesh *m)
{
	meshes.erase(m);
}

void Scene::render(double dtime, ShaderProgram *shader_program)
{
	auto renderlist = meshes;
	for (auto it = renderlist.begin(); it != renderlist.end(); it++) {
		Mesh *mesh = *it;
		mesh->render(dtime, shader_program);
	}
}

void Scene::clear()
{
	meshes.clear();
}

Scene::~Scene()
{
	clear();
}
