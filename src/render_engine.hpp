#pragma once

#include "gl.hpp"

namespace dragonblocks
{	
	class Camera;
	class InputHandler;
	class Scene;
	class Window;

	class RenderEngine
	{
		public:
		Camera *camera;
		Scene *scene;
		Window *window;
		double render_distance = 16;
		double fov = 45;
		glm::vec3 sky;
		
		void render(double);
		bool running();
		
		RenderEngine();
		~RenderEngine();	
	};
}
