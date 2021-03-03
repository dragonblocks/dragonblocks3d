#pragma once

#include "gl.hpp"

namespace dragonblocks
{
	class Camera
	{
		public:
		glm::mat4 getViewMatrix() const;
		void toggleMode();
		void update(double, double, const glm::vec3 &);
		glm::vec3 up() const;
		glm::vec3 front() const;
		glm::vec3 right() const;
		bool thirdPerson() const;
		
		Camera();
		
		private:
		glm::vec3 pos;
		bool m_third_person;
		glm::vec3 m_up;
		glm::vec3 m_world_up;
		glm::vec3 m_front;
		glm::vec3 m_right;
	};
} 
