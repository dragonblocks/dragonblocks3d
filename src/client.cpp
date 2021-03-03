#include <iostream>
#include <stdexcept>
#include "async_mgr.hpp"
#include "client.hpp" 
#include "game.hpp"
#include "gl.hpp"
#include "input_handler.hpp"
#include "local_player.hpp" 
#include "map.hpp" 
#include "mapgen.hpp" 
#include "render_engine.hpp" 
#include "shader_program.hpp" 
#include "texture.hpp" 
#include "window.hpp" 

using namespace std;
using namespace glm;
using namespace dragonblocks;

void Client::run()
{
	async_mgr->start();
	while (render_engine->running()) {
		double dtime = glfwGetTime() - last_time;
		last_time = glfwGetTime();
		
		player->step(dtime);
		
		render_engine->render(dtime);
		
		input_handler->processInput(dtime);
		
		// process keys
		if (input_handler->wasKeyDown(GLFW_KEY_F11)) {
			render_engine->window->toggleFullscreen();
		}
	}
}

Client::Client()
{
	cout << "Initalizing Client..." << endl;
	
	Texture::mipmap = true;
	Texture::bilinear_filter = false;
	Texture::initArgs();
	
	async_mgr = new AsyncMgr;
	
	input_handler = new InputHandler();
	input_handler->mouse_sensitivity = 20;
	input_handler->listenFor(GLFW_KEY_F11);	
	
	render_engine = new RenderEngine;
	render_engine->render_distance = 1000;
	render_engine->fov = 86.1;
	render_engine->sky = vec3(0.52941176470588, 0.8078431372549, 0.92156862745098);		// HTML skyblue
	render_engine->window->setSize(1250, 750);
	render_engine->window->setPos(0, 0);
	render_engine->window->setTitle("Dragonblocks");
	
	input_handler->setWindow(render_engine->window);
	
	shader_program = new ShaderProgram("shaders");
	
	mapgen = new Mapgen;
	
	map = new Map(mapgen, async_mgr, render_engine->scene, shader_program);
	
	Texture player_texture;
	player_texture.load("textures/stone.png");
	
	player = new LocalPlayer(map, render_engine->scene, player_texture, shader_program, render_engine->camera, input_handler);
	player->pitch_move = false;
	player->speed = 10;
	player->setSize(vec3(0.75, 1.5, 0.75));
	
	game = new Game(mapgen);

	last_time = glfwGetTime();

	cout << "Initialisation done." << endl;
}

extern "C" void _dragonblocks_start_client()
{
	Client().run();
}
