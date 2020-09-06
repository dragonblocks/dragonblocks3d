#pragma once

namespace dragonblocks
{
	class Game;
	class Map;
	class Mapgen;
	class RenderEngine;
	
	class Client
	{
		public:
		Game *game;
		Map *map;
		Mapgen *mapgen;
		RenderEngine *render_engine;
		
		Client();
		~Client();
	};
} 
