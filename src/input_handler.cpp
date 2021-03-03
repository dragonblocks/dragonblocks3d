#include "camera.hpp" 
#include "input_handler.hpp" 
#include "window.hpp" 

using namespace std;
using namespace glm;
using namespace dragonblocks;

void InputHandler::processInput(double dtime)
{
	cursor_delta = vec2(mouse_sensitivity * dtime) * (vec2)window->getCursorDelta();
	was_down.clear();
	for (auto it = is_down.begin(); it != is_down.end(); it++) {
		int key = *it;
		if (! window->isKeyDown(key)) {
			was_down.insert(key);
		}
	}
	is_down.clear();
	for (auto it = listened_keys.begin(); it != listened_keys.end(); it++) {
		int key = *it;
		if (window->isKeyDown(key)) {
			is_down.insert(key);
		}
	}
}

void InputHandler::listenFor(int key)
{
	listened_keys.insert(key);
}

void InputHandler::dontListenFor(int key)
{
	listened_keys.erase(key);
}

bool InputHandler::isKeyDown(int key)
{
	return is_down.find(key) != is_down.end();
}

bool InputHandler::wasKeyDown(int key)
{
	return was_down.find(key) != was_down.end();
}

vec2 InputHandler::getCursorDelta()
{
	return cursor_delta;
}

void InputHandler::setWindow(Window *w)
{
	if (! window) {
		window = w;
	}
}
