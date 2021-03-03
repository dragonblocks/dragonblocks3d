#include "animations.hpp"
#include "box_vertices.hpp"
#include "local_entity.hpp" 
#include "mesh.hpp"

using namespace glm;
using namespace dragonblocks;

void LocalEntity::setPos(vec3 p)
{
	mesh->pos = p;
}

vec3 LocalEntity::getPos()
{
	return mesh->pos;
}

void LocalEntity::setSize(vec3 s)
{
	mesh->minp = -(s / 2.0f);
	mesh->maxp = +(s / 2.0f);
	mesh->size = s;
}

vec3 LocalEntity::getSize()
{
	return mesh->size;
}

void LocalEntity::setRotationAxis(vec3 r)
{
	mesh->rotation_axis = r;
}

vec3 LocalEntity::getRotationAxis()
{
	return mesh->rotation_axis;
}

void LocalEntity::setRotationAngle(double r)
{
	mesh->rotation_angle = r;
}

double LocalEntity::getRotationAngle()
{
	return mesh->rotation_angle;
}

void LocalEntity::setVisible(bool v)
{
	mesh->visible = v;
}

bool LocalEntity::isVisible()
{
	return mesh->visible;
}

LocalEntity::LocalEntity(Map *m, Scene *s, const TileDef &t, ShaderProgram *sh) : IEntity(m), tile_def(t)
{
	mesh = new Mesh(s, sh, &box_vertices[0][0][0], 6 * 6 * 5);
	mesh->textures = tile_def.tiles;
	mesh->vertices_per_texture = 6;
}

LocalEntity::~LocalEntity()
{
	mesh->die();
}
