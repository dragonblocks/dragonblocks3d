#pragma once

#include <string>
#include "gl.hpp"

namespace dragonblocks
{
	class RenderEngine;
	
	class Window
	{
		public:
		static Window *create(RenderEngine *);
		static void windowPosCallback(GLFWwindow *, int, int);
		static void framebufferSizeCallback(GLFWwindow *, int, int);
		static void cursorPosCallback(GLFWwindow *, double, double);

		void setTitle(const std::string &);
		void setPos(int, int);
		void setSize(int, int);
		void toggleFullscreen();
		void close();
		void swapBuffers();
		bool shouldClose() const;
		bool wasKeyDown(int) const;
		glm::ivec2 getSize() const;
		glm::ivec2 getCursorPos() const;
		glm::ivec2 getCursorDelta();
		
		~Window();

		private:
		static Window *singleton;
		
		RenderEngine *render_engine;
		GLFWwindow *id;
		bool fullscreen;
		int width, height;
		int nfs_width, nfs_height, nfs_x, nfs_y;
		int cursor_x, cursor_y, cursor_delta_x, cursor_delta_y;
		
		void posInput(int, int);
		void sizeInput(int, int);
		void cursorInput(int, int);
		
		Window(RenderEngine *);
	};
}

