#pragma once

namespace dragonblocks
{
	class Client;
	class Server;
	class Mainmenu;
	
	enum Gametype
	{
		SERVER,
		CLIENT,
		MAINMENU
	};
	
	extern Gametype gametype;
	extern Client *client;
	extern Server *server;
	extern Mainmenu *mainmenu;
}
