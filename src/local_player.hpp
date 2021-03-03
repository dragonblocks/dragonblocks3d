#pragma once

#include <vector>
#include "local_entity.hpp"
#include "gl.hpp"

namespace dragonblocks
{	
	class Camera;
	class InputHandler;
	class Map;
	class Scene;
	class ShaderProgram;
	
	class LocalPlayer : public LocalEntity
	{
		public:	
		bool pitch_move;
		double yaw, pitch;
		
		void step(double);
		
		LocalPlayer(Map *, Scene *, const TileDef &, ShaderProgram *, Camera *,  InputHandler *);
		
		private:		
		static void staticMouseHandler(double, double, double);
		static void staticKeyHandler(double, std::set<int>);

		Camera *camera;
		InputHandler *input_handler;
		
		void keyHandler(double, std::set<int>);
		void loadChunks();
	};
}
