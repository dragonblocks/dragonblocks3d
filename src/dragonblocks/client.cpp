#include "camera.hpp" 
#include "client.hpp" 
#include "game.hpp"
#include "gl.hpp"
#include "input_handler.hpp"
#include "log.hpp" 
#include "map.hpp" 
#include "mapgen.hpp" 
#include "player.hpp" 
#include "render_engine.hpp" 
#include "texture.hpp" 
#include "window.hpp" 

using namespace glm;
using namespace dragonblocks;

Client::Client()
{
	log("Initalizing...");
	
	Texture::mipmap = false;
	Texture::bilinear_filter = false;
	Texture::initArgs();
	
	render_engine = new RenderEngine;
	
	render_engine->window->setSize(1250, 750);
	render_engine->window->setPos(0, 0);
	render_engine->window->setTitle("Dragonblocks");
	render_engine->window->toggleFullscreen();
	render_engine->input_handler->mouse_sensitivity = 20;
	
	render_engine->setSky(vec3(0.52941176470588, 0.8078431372549, 0.92156862745098));
	render_engine->setRenderDistance(1000);
	render_engine->setFov(86.1);
	
	mapgen = new Mapgen;
	
	map = new Map(mapgen, render_engine->mesh_gen_mgr, render_engine->scene);
	
	player = Player::createLocalplayer(render_engine->camera, render_engine->input_handler, map);
	
	player->pitch_move = false;
	player->yaw = -90;
	player->pitch = -80;
	player->speed = 10;
	player->pos = vec3(8, 8, 8);
	
	game = new Game(mapgen);

	log("Initialisation complete.");
}

void Client::start()
{
	render_engine->startMeshGenMgr();
	while (render_engine->running()) {
		render_engine->render();
	}
}
