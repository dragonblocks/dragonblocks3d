#pragma once

#include <vector>
#include "gl.hpp"

namespace dragonblocks
{	
	class Camera;
	class InputHandler;
	class Map;
	
	class Player
	{
		public:
		static Player *createLocalplayer(Camera *, InputHandler *, Map *);

		glm::vec3 pos;
		bool pitch_move;
		double yaw, pitch;
		double speed;
		
		private:
		static Player *localplayer;
		
		static void staticMouseHandler(double, double, double);
		static void staticKeyHandler(double, std::set<int>);

		Camera *camera;
		InputHandler *input_handler;
		Map *map;
		
		void mouseHandler(double, double, double);
		void keyHandler(double, std::set<int>);
		void loadChunks();
		
		Player(Camera *, InputHandler *, Map *);
	};
}
