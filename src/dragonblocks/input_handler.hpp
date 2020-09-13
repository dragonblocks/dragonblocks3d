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
		void processInput(double);
		void listenFor(int);
		void dontListenFor(int);
		void addMouseHandler(void (*)(double, double, double));
		void removeMouseHandler(void (*)(double, double, double));
		void addKeyHandler(void (*)(double, std::set<int>));
		void removeKeyHandler(void (*)(double, std::set<int>));
		
		double mouse_sensitivity;		

		InputHandler(Window *);
		
		private:
		void processMouseInput(double);
		void processKeyInput(double);
		
		Window *window;
		std::set<int> listened_keys;
		std::set<void (*)(double, double, double)> mouse_handlers;
		std::set<void (*)(double, std::set<int>)> key_handlers;
	};
}
