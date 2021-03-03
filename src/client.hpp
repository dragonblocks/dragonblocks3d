#pragma once

namespace dragonblocks
{
	class AsyncMgr;
	class Game;
	class InputHandler;
	class Map;
	class LocalPlayer;
	class Mapgen;
	class RenderEngine;
	class ShaderProgram;
	
	class Client
	{
		public:
		AsyncMgr *async_mgr;
		Game *game;
		InputHandler *input_handler;
		LocalPlayer *player;
		Map *map;
		Mapgen *mapgen;
		RenderEngine *render_engine;
		ShaderProgram *shader_program;
				
		void run();
		
		Client();
		
		private:		
		double last_time;
	};
} 
