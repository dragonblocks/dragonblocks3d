#pragma once

#include <set>

class Frustum;

namespace dragonblocks
{
	class Mesh;
	class ShaderProgram;
	
	class Scene {
		public:
		void add(Mesh *);
		void remove(Mesh *);
		void render(double, ShaderProgram *, Frustum *);
		void clear();
		void run();

		~Scene();
		
		private:
		std::set<Mesh *> meshes;
	};
} 
