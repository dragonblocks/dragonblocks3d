#include "camera.hpp" 
#include "input_handler.hpp" 
#include "window.hpp" 

using namespace std;
using namespace glm;
using namespace dragonblocks;

void InputHandler::processInput(double dtime)
{
	processMouseInput(dtime);
	processKeyInput(dtime);
}

void InputHandler::processMouseInput(double dtime)
{
	vec2 cursor_delta = vec2(mouse_sensitivity * dtime) * (vec2)window->getCursorDelta();
	onMouseMove(dtime, cursor_delta.x, cursor_delta.y);
}

void InputHandler::processKeyInput(double dtime)
{
	map<int, bool> keysDown;
	for (auto it = listened_keys.begin(); it != listened_keys.end(); it++) {
		if (window->wasKeyDown(it->first)) {
			keysDown[it->first] = true;
		}
	}
	onKeyPress(dtime, keysDown);
}

void InputHandler::onMouseMove(double dtime, double x, double y)
{
	yaw += x;
	pitch -= y;
	camera->update(yaw, pitch);
}

void InputHandler::onKeyPress(double dtime, map<int, bool> keysDown)
{
	vec3 vel = vec3(speed * dtime);
	vec3 front = camera->front(), right = camera->right(), up = camera->up();
	if (! pitch_move) {
		front = normalize(vec3(front.x, 0, front.z));
		up = normalize(vec3(0, up.y, 0));
	}
	if (keysDown[GLFW_KEY_W]) {
		camera->pos += vel * front;
	} else if (keysDown[GLFW_KEY_S]) {
		camera->pos -= vel * front;
	}
	if (keysDown[GLFW_KEY_D]) {
		camera->pos += vel * right;
	} else if (keysDown[GLFW_KEY_A]) {
		camera->pos -= vel * right;
	}
	if (keysDown[GLFW_KEY_SPACE]) {
		camera->pos += vel * up;
	} else if (keysDown[GLFW_KEY_LEFT_SHIFT]) {
		camera->pos -= vel * up;
	}	
}

void InputHandler::listenFor(int key)
{
	listened_keys[key] = true;
}

void InputHandler::dontListenFor(int key)
{
	listened_keys.erase(key);
}

InputHandler::InputHandler(Camera *c, Window *w) : camera(c), window(w)
{
	listenFor(GLFW_KEY_W);
	listenFor(GLFW_KEY_A);
	listenFor(GLFW_KEY_S);
	listenFor(GLFW_KEY_D);
	listenFor(GLFW_KEY_SPACE);
	listenFor(GLFW_KEY_LEFT_SHIFT);
}

