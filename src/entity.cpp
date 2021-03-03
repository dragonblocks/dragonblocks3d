#include "entity.hpp"

using namespace glm;
using namespace dragonblocks;

void IEntity::setPos(vec3 p)
{
}

vec3 IEntity::getPos()
{
	return vec3(0);
}

void IEntity::setSize(vec3 s)
{
}

vec3 IEntity::getSize()
{
	return vec3(0);
}

void IEntity::setRotationAxis(vec3 r)
{
}

vec3 IEntity::getRotationAxis()
{
	return vec3(0);
}

void IEntity::setRotationAngle(double r)
{
}

double IEntity::getRotationAngle()
{
	return 0.0;
}

void IEntity::setVisible(bool v)
{
}

bool IEntity::isVisible()
{
	return false;
}

IEntity::IEntity(Map *m) : map(m)
{
}
