#include "mesh.hpp"
#include "scene.hpp"

using namespace std;
using namespace dragonblocks;

void Scene::add(Mesh *m)
{
	list[m] = true;
}

void Scene::remove(Mesh *m)
{
	list.erase(m);
}

void Scene::render(double dtime, ShaderProgram *shader_program)
{
	for (auto it = list.begin(); it != list.end(); it++) {
		it->first->render(dtime, shader_program);
	}
}

void Scene::clear()
{
	list.clear();
}

Scene::~Scene()
{
	clear();
}
