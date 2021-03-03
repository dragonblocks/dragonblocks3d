#include <stdexcept>
#include "camera.hpp"
#include "input_handler.hpp"
#include "local_player.hpp"
#include "map.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

void LocalPlayer::step(double dtime)
{
	// Cursor input
	vec2 cd = input_handler->getCursorDelta();
	yaw += cd.x;
	pitch -= cd.y;
	pitch = clamp(pitch, -89.0, 89.0);
	
	// Key input
	vec3 pos = getPos();
	vec3 vel = vec3(speed * dtime);
	vec3 front = camera->front(), right = camera->right(), up = camera->up();
	if (! pitch_move) {
		front = normalize(vec3(front.x, 0, front.z));
		up = normalize(vec3(0, up.y, 0));
	}
	if (input_handler->isKeyDown(GLFW_KEY_W)) {
		pos += vel * front;
	} else if (input_handler->isKeyDown(GLFW_KEY_S)) {
		pos -= vel * front;
	}
	if (input_handler->isKeyDown(GLFW_KEY_D)) {
		pos += vel * right;
	} else if (input_handler->isKeyDown(GLFW_KEY_A)) {
		pos -= vel * right;
	}
	if (input_handler->isKeyDown(GLFW_KEY_SPACE)) {
		pos += vel * up;
	} else if (input_handler->isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		pos -= vel * up;
	}
	
	if (input_handler->wasKeyDown(GLFW_KEY_C)) {
		camera->toggleMode();
	}
	
	camera->update(yaw, pitch, pos);
	setPos(pos);
	setVisible(camera->thirdPerson());
	loadChunks();
}

void LocalPlayer::loadChunks()
{
	int dist = 4;
	ivec3 chunkp = Map::getChunkPos(getPos());
	for (int x = chunkp.x - dist; x <= chunkp.x + dist; x++) {
		for (int y = chunkp.y - dist; y < chunkp.y + dist; y++) {
			for (int z = chunkp.z - dist; z <= chunkp.z + dist; z++) {
				map->createChunk(ivec3(x, y, z));
			}
		}
	}
}

LocalPlayer::LocalPlayer(Map *m, Scene *s, const TileDef &t, ShaderProgram *sh, Camera *c, InputHandler *i) : LocalEntity(m, s, t, sh), camera(c), input_handler(i)
{
	input_handler->listenFor(GLFW_KEY_W);
	input_handler->listenFor(GLFW_KEY_A);
	input_handler->listenFor(GLFW_KEY_S);
	input_handler->listenFor(GLFW_KEY_D);
	input_handler->listenFor(GLFW_KEY_SPACE);
	input_handler->listenFor(GLFW_KEY_LEFT_SHIFT);
	input_handler->listenFor(GLFW_KEY_C);
}
