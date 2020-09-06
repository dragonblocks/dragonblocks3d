#pragma once

#include <map>

namespace dragonblocks
{
	class Mesh;
	class ShaderProgram;
	
	class Scene {
		public:
		void add(Mesh *);
		void remove(Mesh *);
		void render(double, ShaderProgram *);
		void clear();

		~Scene();
		
		private:
		std::map<Mesh *, bool> list;
	};
} 
