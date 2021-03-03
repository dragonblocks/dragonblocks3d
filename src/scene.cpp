#include "mesh.hpp"
#include "scene.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

void Scene::add(Mesh *m)
{
	meshes.insert(m);
}

void Scene::remove(Mesh *m)
{
	meshes.erase(m);
}

void Scene::render(double dtime, Frustum *frustum, mat4 projection_matrix, mat4 view_matrix, vec3 sky)
{
	auto renderlist = meshes;
	for (auto it = renderlist.begin(); it != renderlist.end(); it++) {
		Mesh *mesh = *it;
		mesh->render(dtime, frustum, projection_matrix, view_matrix, sky);
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
