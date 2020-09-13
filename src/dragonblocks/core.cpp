#include "core.hpp"
#include "client.hpp"
#include "render_engine.hpp"

using namespace dragonblocks;

Gametype dragonblocks::gametype;
Client *dragonblocks::client = nullptr;

extern "C" void _dragonblocks_start_client()
{
	gametype = Gametype::CLIENT; 
	client = new Client();
	client->start();
}
