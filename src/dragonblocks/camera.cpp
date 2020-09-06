#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp" 

using namespace glm;
using namespace dragonblocks;

mat4 Camera::getViewMatrix() const
{
	return lookAt(pos, pos + m_front, m_up);
}

void Camera::update(double yaw, double pitch)
{
	yaw = radians(yaw);
	pitch = radians(clamp(pitch, -89.0, 89.0));
	
	m_front = normalize(vec3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)));
	m_right = normalize(cross(m_front, m_world_up));
	m_up = normalize(cross(m_right, m_front));
}

vec3 Camera::up() const
{
	return m_up;
}

vec3 Camera::front() const
{
	return m_front;
}

vec3 Camera::right() const
{
	return m_right;
}

Camera::Camera() : pos(0, 0, 0), m_up(0, 1, 0), m_world_up(0, 1, 0), m_front(0, 0, -1)
{
}
