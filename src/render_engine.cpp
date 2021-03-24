#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include "FrustumCull.h"
#include "camera.hpp"
#include "input_handler.hpp"
#include "render_engine.hpp"
#include "scene.hpp"
#include "shader_program.hpp"
#include "window.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

void RenderEngine::render(double dtime)
{
	glClearColor(sky.r, sky.g, sky.b, 1.0); CHECKERR

	/*
		glEnable(GL_CULL_FACE); CHECKERR
		glCullFace(GL_BACK); CHECKERR
		glFrontFace(GL_CW); CHECKERR
	*/

	glEnable(GL_DEPTH_TEST); CHECKERR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECKERR


	dvec2 window_size = window->getSize();
	mat4 projection_matrix = perspective(radians(fov), window_size.x / window_size.y, 0.01, render_distance);

	mat4 view_matrix = camera->getViewMatrix();

	Frustum frustum(projection_matrix * view_matrix);

	scene->render(dtime, &frustum, projection_matrix, view_matrix, sky);

	window->swapBuffers(); CHECKERR
	glfwPollEvents(); CHECKERR
}

bool RenderEngine::running()
{
	return ! window->shouldClose();
}

RenderEngine::RenderEngine()
{
	if (! glfwInit()) {
		throw runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = Window::create(this);
	camera = new Camera;
	scene = new Scene;

	GLenum glew_init_err = glewInit();
	if (glew_init_err != GLEW_OK) {
		throw runtime_error("Failed to initialize GLEW");
	}
}

RenderEngine::~RenderEngine()
{
	delete window;
	delete camera;
	delete scene;
}
