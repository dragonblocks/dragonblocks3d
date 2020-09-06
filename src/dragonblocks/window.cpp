#include <stdexcept>
#include "render_engine.hpp"
#include "window.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;
	
Window *Window::singleton = nullptr;

Window *Window::create(RenderEngine *r)
{
	if (singleton)
		throw runtime_error("Window already exists");
	return singleton = new Window(r);
}

void Window::windowPosCallback(GLFWwindow *id, int x, int y)
{
	singleton->posInput(x, y);
}

void Window::framebufferSizeCallback(GLFWwindow *id, int width, int height)
{
	glViewport(0, 0, width, height);
	singleton->render_engine->updateProjectionMatrix();
	singleton->sizeInput(width, height);
}

void Window::cursorPosCallback(GLFWwindow *id, double x, double y)
{
	singleton->cursorInput(x, y);
}

void Window::setTitle(const string &title)
{
	glfwSetWindowTitle(id, title.c_str());
}

void Window::setSize(int width, int height)
{
	glfwSetWindowSize(id, width, height);
}

void Window::setPos(int x, int y)
{
	glfwSetWindowPos(id, x, y);
}

void Window::toggleFullscreen()
{
	fullscreen = ! fullscreen;
	
	if (fullscreen) {
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(id, monitor, 0, 0, vidmode->width, vidmode->height, 0);
	}
	else
		glfwSetWindowMonitor(id, nullptr, nfs_x, nfs_y, nfs_width, nfs_height, 0);
}

void Window::close()
{
	glfwDestroyWindow(id);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(id);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(id);
}

bool Window::wasKeyDown(int key) const
{
	return glfwGetKey(id, key) == GLFW_PRESS;
}

ivec2 Window::getSize() const
{
	return ivec2(width, height);
}

ivec2 Window::getCursorPos() const
{
	return ivec2(cursor_x, cursor_y);
}

ivec2 Window::getCursorDelta()
{
	ivec2 delta(cursor_delta_x, cursor_delta_y);
	cursor_delta_x = cursor_delta_y = 0;
	return delta;
}

void Window::posInput(int x, int y)
{
	if (! fullscreen) {
		nfs_x = x;
		nfs_y = y;
	}
}

void Window::sizeInput(int w, int h)
{
	width = w;
	height = h;
	if (! fullscreen) {
		nfs_width = width;
		nfs_height = height;
	}
}

void Window::cursorInput(int x, int y)
{
	int lx = cursor_x;
	int ly = cursor_y;
	cursor_delta_x = x - lx;
	cursor_delta_y = y - ly;
	cursor_x = x;
	cursor_y = y;
}

Window::~Window()
{
	close();
}

Window::Window(RenderEngine *r) : render_engine(r)
{
	fullscreen = false;
	width = nfs_width = 100;
	height = nfs_height = 100;
	cursor_x = cursor_y = cursor_delta_x = cursor_delta_y = 0;
	id = glfwCreateWindow(width, height, "libdragonblocks.so", NULL, NULL);
	if (! id) {
		glfwTerminate();
		throw runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(id);
	glfwSetInputMode(id, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetWindowPosCallback(id, Window::windowPosCallback);
	glfwSetFramebufferSizeCallback(id, Window::framebufferSizeCallback);
	glfwSetCursorPosCallback(id, Window::cursorPosCallback);
}


