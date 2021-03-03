#pragma once

#include "async_mgr.hpp"
#include "entity.hpp"
#include "gl.hpp"
#include "tile_def.hpp"

namespace dragonblocks
{
	class Map;
	class Mesh;
	class Scene;
	class ShaderProgram;
	
	class LocalEntity : public IEntity
	{
		public:
		void setPos(glm::vec3);
		glm::vec3 getPos();
		void setSize(glm::vec3);
		glm::vec3 getSize();
		void setRotationAxis(glm::vec3);
		glm::vec3 getRotationAxis();
		void setRotationAngle(double);
		double getRotationAngle();
		void setVisible(bool);
		bool isVisible();
		void step(double);
		
		LocalEntity(Map *, Scene *, const TileDef &, ShaderProgram *);
		~LocalEntity();
		
		protected:
		TileDef tile_def;
		Mesh *mesh;
	};
}
