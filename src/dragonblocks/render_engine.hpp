#pragma once

#include "gl.hpp"

namespace dragonblocks
{	
	class Camera;
	class InputHandler;
	class MeshGenThread;
	class ShaderProgram;
	class Scene;
	class Window;

	class RenderEngine
	{
		public:
		static RenderEngine *create();

		Camera *camera;
		InputHandler *input_handler;
		MeshGenThread *mesh_gen_thread;
		Scene *scene;
		ShaderProgram *shader_program;
		Window *window;
		
		void render();
		void loadChunks();
		void loop();
		void updateViewMatrix();
		void updateProjectionMatrix();
		void setSky(glm::vec3);
		void setRenderDistance(double);
		void setFov(double);
		
		~RenderEngine();
		
		private:
		static RenderEngine *singleton;
		
		double last_time;
		double render_distance;
		double fov;
		
		RenderEngine();
	};
}
