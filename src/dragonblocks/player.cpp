#include <stdexcept>
#include "camera.hpp"
#include "input_handler.hpp"
#include "map.hpp"
#include "player.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

Player* Player::localplayer = nullptr;

Player *Player::createLocalplayer(Camera *c, InputHandler *i, Map *m)
{
	if (localplayer)
		throw runtime_error("Localplayer already exists");
	return localplayer = new Player(c, i, m);
}

void Player::staticMouseHandler(double dtime, double x, double y)
{
	localplayer->mouseHandler(dtime, x, y);
}

void Player::staticKeyHandler(double dtime, set<int> keys)
{
	localplayer->keyHandler(dtime, keys);
}

void Player::mouseHandler(double dtime, double x, double y)
{
	yaw += x;
	pitch -= y;
	pitch = clamp(pitch, -89.0, 89.0);
	camera->update(yaw, pitch);
}

void Player::keyHandler(double dtime, set<int> keys)
{
	vec3 vel = vec3(speed * dtime);
	vec3 front = camera->front(), right = camera->right(), up = camera->up();
	if (! pitch_move) {
		front = normalize(vec3(front.x, 0, front.z));
		up = normalize(vec3(0, up.y, 0));
	}
	if (keys.find(GLFW_KEY_W) != keys.end()) {
		pos += vel * front;
	} else if (keys.find(GLFW_KEY_S) != keys.end()) {
		pos -= vel * front;
	}
	if (keys.find(GLFW_KEY_D) != keys.end()) {
		pos += vel * right;
	} else if (keys.find(GLFW_KEY_A) != keys.end()) {
		pos -= vel * right;
	}
	if (keys.find(GLFW_KEY_SPACE) != keys.end()) {
		pos += vel * up;
	} else if (keys.find(GLFW_KEY_LEFT_SHIFT) != keys.end()) {
		pos -= vel * up;
	}
	camera->pos = pos;
	loadChunks();
}

void Player::loadChunks()
{
	ivec3 chunkp = Map::getChunkPos(pos);
	for (int x = chunkp.x - 1; x <= chunkp.x + 1; x++) {
		for (int y = chunkp.y - 1; y < chunkp.y + 1; y++) {
			for (int z = chunkp.z - 1; z <= chunkp.z + 1; z++) {
				map->createChunk(ivec3(x, y, z));
			}
		}
	}
}

Player::Player(Camera *c, InputHandler *i, Map *m) : camera(c), input_handler(i), map(m)
{
	input_handler->listenFor(GLFW_KEY_W);
	input_handler->listenFor(GLFW_KEY_A);
	input_handler->listenFor(GLFW_KEY_S);
	input_handler->listenFor(GLFW_KEY_D);
	input_handler->listenFor(GLFW_KEY_SPACE);
	input_handler->listenFor(GLFW_KEY_LEFT_SHIFT);
	
	input_handler->addMouseHandler(Player::staticMouseHandler);
	input_handler->addKeyHandler(Player::staticKeyHandler);
}
