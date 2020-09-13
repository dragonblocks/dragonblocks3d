#pragma once

#include "gl.hpp"

namespace dragonblocks
{	
	class Camera;
	class InputHandler;
	class MeshGenMgr;
	class ShaderProgram;
	class Scene;
	class Window;

	class RenderEngine
	{
		public:
		Camera *camera;
		InputHandler *input_handler;
		MeshGenMgr *mesh_gen_mgr;
		Scene *scene;
		ShaderProgram *shader_program;
		Window *window;
		
		void render();
		bool running();
		void updateViewMatrix();
		void updateProjectionMatrix();
		void setSky(glm::vec3);
		void setRenderDistance(double);
		void setFov(double);
		void startMeshGenMgr();
		
		
		RenderEngine();
		~RenderEngine();
		
		private:		
		double last_time;
		double render_distance;
		double fov;
	};
}
