#include "core.hpp"
#include "client.hpp"
#include "render_engine.hpp"
#include "server.hpp"
#include "mainmenu.hpp"

using namespace dragonblocks;

Gametype dragonblocks::gametype;
Client *dragonblocks::client = nullptr;
Server *dragonblocks::server = nullptr;
Mainmenu *dragonblocks::mainmenu = nullptr;

extern "C" void _dragonblocks_start_client()
{
	gametype = Gametype::CLIENT; 
	client = new Client();
	client->render_engine->loop();
}

extern "C" void _dragonblocks_start_server()
{
	gametype = Gametype::SERVER;
	server = new Server();
}

extern "C" void _dragonblocks_start_mainmenu()
{
	gametype = Gametype::MAINMENU;
	mainmenu = new Mainmenu();
}
