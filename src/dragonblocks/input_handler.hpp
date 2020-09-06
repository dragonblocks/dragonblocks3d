#pragma once

#include <map>
#include "gl.hpp"

namespace dragonblocks
{
	class Camera;
	class Window;
	
	class InputHandler
	{
		public:
		void processInput(double);
		void processMouseInput(double);
		void processKeyInput(double);
		void onMouseMove(double, double, double);
		void onKeyPress(double, std::map<int, bool>);
		void listenFor(int);
		void dontListenFor(int);
		
		bool pitch_move;
		double mouse_sensitivity;		
		double yaw, pitch;
		double speed;
		
		InputHandler(Camera *, Window *);
		
		private:		
		Camera *camera;
		Window *window;
		std::map<int, bool> listened_keys;
	};
}
