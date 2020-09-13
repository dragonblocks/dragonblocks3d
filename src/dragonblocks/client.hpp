#pragma once

namespace dragonblocks
{
	class Game;
	class Map;
	class Mapgen;
	class Player;
	class RenderEngine;
	
	class Client
	{
		public:
		Game *game;
		Map *map;
		Mapgen *mapgen;
		Player *player;
		RenderEngine *render_engine;
		
		void start();
		
		Client();
		~Client();
	};
} 
