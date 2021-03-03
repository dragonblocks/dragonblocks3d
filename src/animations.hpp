#pragma once

#include "gl.hpp"
#include "mesh.hpp"

namespace dragonblocks
{
	class FlyInAnimation : public Mesh::IAnimation 
	{
		public:
		double last_for;
		double offset;
		
		glm::vec3 getPos(glm::vec3);
		
		FlyInAnimation(double = 0.4, double = 20.0, void (*)(void *) = nullptr, void * = nullptr);
	};
	
	class GrowAnimation : public Mesh::IAnimation 
	{
		public:
		double last_for;
		
		glm::vec3 getSize(glm::vec3);
		
		GrowAnimation(double = 0.25, void (*)(void *) = nullptr, void * = nullptr);
	};
	
	class RotateAnimation : public Mesh::IAnimation 
	{
		public:
		double speed;
		
		float getRotationAngle(float);
		
		RotateAnimation(double = 1.0);
	};
} 
