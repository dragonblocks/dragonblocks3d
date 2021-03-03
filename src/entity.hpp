#pragma once

#include "async_mgr.hpp"
#include "gl.hpp"
#include "tile_def.hpp"

namespace dragonblocks
{
	class Map;
	
	class IEntity
	{
		public:
		/*double vertical_speed;
		double vertical_acceleration;
		double horizontal_speed;
		double horizontal_max_speed;
		double horizontal_acceleration;
		glm::vec3 horizontal_move_dir;
		glm::vec3 vertical_move_dir;
		*/
		double speed;
		
		virtual void setPos(glm::vec3);
		virtual glm::vec3 getPos();
		virtual void setSize(glm::vec3);
		virtual glm::vec3 getSize();
		virtual void setRotationAxis(glm::vec3);
		virtual glm::vec3 getRotationAxis();
		virtual void setRotationAngle(double);
		virtual double getRotationAngle();
		virtual void setVisible(bool);
		virtual bool isVisible();
		
		protected:
		Map *map;
		
		IEntity(Map *);
	};
}
