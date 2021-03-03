#include <glm/gtc/constants.hpp>
#include "animations.hpp"

using namespace glm;
using namespace dragonblocks;

vec3 FlyInAnimation::getPos(vec3 pos)
{
	pos.y -= offset * time_left / last_for;
	return pos;
}

FlyInAnimation::FlyInAnimation(double l, double o, void (*on)(void *), void *e) : Mesh::IAnimation(l, on, e), last_for(l), offset(o)
{
}

vec3 GrowAnimation::getSize(vec3 size)
{
	size *= 1 - time_left / last_for;
	return size;
}

GrowAnimation::GrowAnimation(double l, void (*o)(void *), void *e) : Mesh::IAnimation(l, o, e), last_for(l)
{
}

float RotateAnimation::getRotationAngle(float rotation_angle)
{
	rotation_angle += glfwGetTime() * speed * pi<float>() * 2;
	return rotation_angle;
}

RotateAnimation::RotateAnimation(double s) : speed(s)
{
}
