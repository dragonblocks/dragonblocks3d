#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>
#include "FrustumCull.h"
#include "mesh.hpp"
#include "scene.hpp"
#include "shader_program.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

bool Mesh::IAnimation::expired(double dtime)
{
	if (expires) {
		time_left -= dtime;
		if (time_left < 0) {
			if (on_finish) {
				(*on_finish)(extra_data);
			}
			return true;
		}
	}
	return false;
}

vec3 Mesh::IAnimation::getPos(vec3 p)
{
	return p;
}

vec3 Mesh::IAnimation::getSize(vec3 s)
{
	return s;
}

vec3 Mesh::IAnimation::getRotationAxis(vec3 r)
{
	return r;
}

float Mesh::IAnimation::getRotationAngle(float r)
{
	return r;
}

Mesh::IAnimation::IAnimation(double t, void (*o)(void *), void *e) : time_left(t), on_finish(o), extra_data(e)
{
	expires = true;
}

void Mesh::render(double dtime, Frustum *frustum, mat4 projection_matrix, mat4 view_matrix, vec3 sky)
{
	rendering = true;
	
	if (do_delete) {
		delete this;
		return;
	} else if (prepare_death) {
		do_delete = true;
	}
	
	if (! configured) {
		configure();
	}

	shader_program->use(); CHECKERR
	
	mat4 model_matrix = identity<mat4>();

	vec3 n_pos = pos, n_size = size, n_rotation_axis = rotation_axis;
	float n_rotation_angle = rotation_angle;

	if (animation) {
		if (animation->expired(dtime)) {
			delete animation;
			animation = nullptr;
		} else {
			n_pos = animation->getPos(n_pos);
			n_size = animation->getSize(n_size);
			n_rotation_axis = animation->getRotationAxis(n_rotation_axis);
			n_rotation_angle = animation->getRotationAngle(n_rotation_angle);
		}
	}

	model_matrix = translate(model_matrix, n_pos);
	model_matrix = rotate(model_matrix, n_rotation_angle, n_rotation_axis);
	model_matrix = scale(model_matrix, n_size);
	
	if (! visible || ! frustum->IsBoxVisible(model_matrix * vec4(minp - vec3(1.0), 1.0), model_matrix * vec4(maxp + vec3(1.0), 1.0)))
		return;
	
	shader_program->set("model", model_matrix); CHECKERR
	shader_program->set("view", view_matrix); CHECKERR
	shader_program->set("projection", projection_matrix); CHECKERR
	shader_program->set("sky", sky); CHECKERR
	
	glBindVertexArray(VAO); CHECKERR
	for (int i = 0; i < textures.size(); i++) {
		textures[i].bind(); CHECKERR
		glDrawArrays(GL_TRIANGLES, i * vertices_per_texture, vertices_per_texture); CHECKERR
	}
	glBindVertexArray(0); CHECKERR
	glBindTexture(GL_TEXTURE_2D, 0); CHECKERR
	
	rendering = false;
}

bool Mesh::isRendering()
{
	return rendering;
}

void Mesh::die()
{
	prepare_death = true;
}

Mesh::Mesh(Scene *s, ShaderProgram *sh, const GLfloat *v, GLsizei vs): pos(0), size(1), rotation_axis(0, 1, 0), scene(s), shader_program(sh), vertices_size(vs * sizeof(GLfloat))
{
	if (! v || ! vs)
		throw runtime_error("Invalid Mesh configuration");
	vertices = malloc(vertices_size);
	memcpy(vertices, v, vertices_size);
	scene->add(this);
}

Mesh::~Mesh()
{
	scene->remove(this);
	if (VAO) {
		glDeleteVertexArrays(1, &VAO); CHECKERR
	}
	if (VBO) {
		glDeleteBuffers(1, &VAO); CHECKERR
	}
	if (animation) {
		delete animation;
	}
}

void Mesh::configure()
{		
	glGenVertexArrays(1, &VAO); CHECKERR
	glGenBuffers(1, &VBO); CHECKERR
	
	glBindVertexArray(VAO); CHECKERR
	glBindBuffer(GL_ARRAY_BUFFER, VBO); CHECKERR

	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW); CHECKERR
	
	GLsizei stride = 5 * sizeof(GLfloat); CHECKERR
	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (GLvoid *)(0 * sizeof(GLfloat))); CHECKERR
	glEnableVertexAttribArray(0); CHECKERR
	glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (GLvoid *)(3 * sizeof(GLfloat))); CHECKERR
	glEnableVertexAttribArray(1); CHECKERR
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); CHECKERR
	glBindVertexArray(0); CHECKERR
	
	free(vertices);
	vertices = NULL;
	configured = true;
}
