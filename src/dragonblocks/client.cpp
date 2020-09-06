#include "camera.hpp" 
#include "client.hpp" 
#include "game.hpp"
#include "gl.hpp"
#include "input_handler.hpp"
#include "log.hpp" 
#include "map.hpp" 
#include "mapgen.hpp" 
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
	
	render_engine = RenderEngine::create();
	
	render_engine->window->setSize(1250, 750);
	render_engine->window->setPos(0, 0);
	render_engine->window->setTitle("Dragonblocks");
	render_engine->window->toggleFullscreen();
	render_engine->camera->pos = vec3(8, 8, 8);
	render_engine->input_handler->mouse_sensitivity = 20;
	render_engine->input_handler->pitch_move = false;
	render_engine->input_handler->yaw = -90;
	render_engine->input_handler->pitch = -80;
	render_engine->input_handler->speed = 10;
	render_engine->setSky(vec3(0.52941176470588, 0.8078431372549, 0.92156862745098));
	render_engine->setRenderDistance(1000);
	render_engine->setFov(86.1);
	
	mapgen = new Mapgen;
	
	map = new Map(mapgen, render_engine->mesh_gen_thread, render_engine->scene);
	
	game = new Game(mapgen);
	
	log("Initialisation complete.");
}
