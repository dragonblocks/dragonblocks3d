#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"
#include "client.hpp" 						// ugly, only keep until player is implemented
#include "core.hpp" 						// this one too
#include "gldebug.hpp"
#include "input_handler.hpp"
#include "map.hpp"  						// this one three
#include "mesh_gen_mgr.hpp"
#include "render_engine.hpp"
#include "scene.hpp"
#include "shader_program.hpp"
#include "window.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

void RenderEngine::render()
{
	double dtime = glfwGetTime() - last_time;
	last_time = glfwGetTime();
	
	input_handler->processInput(dtime);
	
	glEnable(GL_DEPTH_TEST); CHECKERR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECKERR

	updateViewMatrix();	CHECKERR
	
	scene->render(dtime, shader_program);
	
	window->swapBuffers(); CHECKERR
	glfwPollEvents(); CHECKERR
}

void RenderEngine::loadChunks()
{
	ivec3 chunkp = Map::getChunkPos(camera->pos);
	for (int x = chunkp.x - 1; x <= chunkp.x + 1; x++) {
		for (int y = chunkp.y - 1; y < chunkp.y + 1; y++) {
			for (int z = chunkp.z - 1; z <= chunkp.z + 1; z++) {
				client->map->createChunk(ivec3(x, y, z));
			}
		}
	}
}

void RenderEngine::loop()
{
	while (! window->shouldClose()) {
		render();
		loadChunks();
	}
}

void RenderEngine::updateProjectionMatrix()
{
	dvec2 bounds = window->getSize();
	mat4 projection_matrix = perspective(radians(fov), bounds.x / bounds.y, 0.01, render_distance);
	shader_program->set("projection", projection_matrix); CHECKERR
}

void RenderEngine::updateViewMatrix()
{
	shader_program->set("view", camera->getViewMatrix()); CHECKERR
}

void RenderEngine::setSky(vec3 sky)
{
	glClearColor(sky.r, sky.g, sky.b, 1.0); CHECKERR
	shader_program->set("sky", sky); CHECKERR
}

void RenderEngine::setRenderDistance(double d)
{
	render_distance = d;
	updateProjectionMatrix();
}

void RenderEngine::setFov(double f)
{
	fov = f;
	updateProjectionMatrix();
}

RenderEngine::RenderEngine()
{
	if (! glfwInit())
		throw runtime_error("Failed to initialize GLFW");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = Window::create(this);
	camera = new Camera;
	input_handler = new InputHandler(camera, window);
	mesh_gen_mgr = new MeshGenMgr;
	scene = new Scene;
	
	GLenum glew_init_err = glewInit();
	if (glew_init_err != GLEW_OK)
		throw runtime_error("Failed to initialize GLEW");

	shader_program = new ShaderProgram("shaders");

	setSky(vec3(1.0, 1.0, 1.0));
	setRenderDistance(16);
	setFov(45);
	
	last_time = glfwGetTime();
}

RenderEngine::~RenderEngine()
{
	delete window;
	delete camera;
	delete input_handler;
	delete mesh_gen_mgr;
	delete scene;
	delete shader_program;
}
