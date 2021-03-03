#pragma once

#include <set>
#include "gl.hpp"

class Frustum;

namespace dragonblocks
{
	class Mesh;
	class ShaderProgram;
	
	class Scene {
		public:
		void add(Mesh *);
		void remove(Mesh *);
		void render(double, Frustum *, glm::mat4, glm::mat4, glm::vec3);
		void clear();
		void run();

		~Scene();
		
		private:
		std::set<Mesh *> meshes;
	};
} 
