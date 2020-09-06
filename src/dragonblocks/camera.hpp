#pragma once

#include "gl.hpp"

namespace dragonblocks
{
	class Camera
	{
		public:
		glm::vec3 pos;
		
		glm::mat4 getViewMatrix() const;
		void update(double, double);
		glm::vec3 up() const;
		glm::vec3 front() const;
		glm::vec3 right() const;
		
		Camera();
		
		private:		
		glm::vec3 m_up;
		glm::vec3 m_world_up;
		glm::vec3 m_front;
		glm::vec3 m_right;
	};
} 
