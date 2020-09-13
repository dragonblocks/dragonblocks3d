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

void InputHandler::listenFor(int key)
{
	listened_keys.insert(key);
}

void InputHandler::dontListenFor(int key)
{
	listened_keys.erase(key);
}

void InputHandler::addMouseHandler(void (*callback)(double, double, double))
{
	mouse_handlers.insert(callback);
}

void InputHandler::removeMouseHandler(void (*callback)(double, double, double))
{
	mouse_handlers.erase(callback);
}

void InputHandler::addKeyHandler(void (*callback)(double, set<int>))
{
	key_handlers.insert(callback);
}

void InputHandler::removeKeyHandler(void (*callback)(double, set<int>))
{
	key_handlers.erase(callback);
}

InputHandler::InputHandler(Window *w) : window(w)
{
}

void InputHandler::processMouseInput(double dtime)
{
	vec2 cursor_delta = vec2(mouse_sensitivity * dtime) * (vec2)window->getCursorDelta();
	double x, y;
	x = cursor_delta.x;
	y = cursor_delta.y;
	if (x != 0 && y != 0) {
		for (auto it = mouse_handlers.begin(); it != mouse_handlers.end(); it++) {
			(**it)(dtime, x, y);
		}
	}
}

void InputHandler::processKeyInput(double dtime)
{
	set<int> keysDown;
	for (auto it = listened_keys.begin(); it != listened_keys.end(); it++) {
		int key = *it;
		if (window->wasKeyDown(key)) {
			keysDown.insert(key);
		}
	}
	if (keysDown.begin() != keysDown.end()) {
		for (auto it = key_handlers.begin(); it != key_handlers.end(); it++) {
			(**it)(dtime, keysDown);
		}
	}
}
