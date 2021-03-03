#pragma once

#include <set>
#include "gl.hpp"

namespace dragonblocks
{
	class Camera;
	class Window;
	
	class InputHandler
	{
		public:
		double mouse_sensitivity;
		
		void processInput(double);
		void listenFor(int);
		void dontListenFor(int);
		bool isKeyDown(int);
		bool wasKeyDown(int);
		glm::vec2 getCursorDelta();
		void setWindow(Window *);
		
		private:
		Window *window;
		std::set<int> listened_keys;
		std::set<int> is_down;
		std::set<int> was_down;
		glm::vec2 cursor_delta;
	};
}
