#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "gldebug.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "shader_program.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

double Mesh::Effect::grow_time = 0.25;	// s
double Mesh::Effect::flyin_time = 0.4;	// s
double Mesh::Effect::flyin_offset = 20;	// m
double Mesh::Effect::rotate_speed = 1;	// turns/s

mat4 Mesh::Effect::getModelMatrix(double dtime, vec3 pos, vec3 size, vec3 rotation_axis, float rotation_angle)
{
	mat4 trans = mat4(1.0);

	if (type == Mesh::Effect::Type::NONE)
		goto finish;

	if (expires) {
		time_left -= dtime;
		if (time_left < 0) {
			type = Mesh::Effect::Type::NONE;
			if (on_finish) {
				(*on_finish)(extra_data);
			}
			goto finish;
		}
	}	

	switch (type) {
		case Mesh::Effect::Type::FLYIN:
		pos.y -= Mesh::Effect::flyin_offset * time_left / Mesh::Effect::flyin_time;
		break;
		
		case Mesh::Effect::Type::GROW:
		size *= 1 - time_left / Mesh::Effect::grow_time;
		break;
		
		case Mesh::Effect::Type::ROTATE:
		rotation_angle += glfwGetTime() * Mesh::Effect::rotate_speed * pi<float>() * 2;
	}

	finish:
	
	trans = translate(trans, pos);
	trans = rotate(trans, rotation_angle, rotation_axis);
	trans = scale(trans, size);
	
	return trans;
}

Mesh::Effect::Effect(Mesh::Effect::Type t, void (*o)(void *), void *e) : type(t), on_finish(o), extra_data(e)
{
	switch(type) {
		case Mesh::Effect::Type::FLYIN:
		expires = true;
		time_left = Mesh::Effect::flyin_time;
		break;
		
		case Mesh::Effect::Type::GROW:
		expires = true;
		time_left = Mesh::Effect::grow_time;
		break;
		
		case Mesh::Effect::Type::ROTATE:
		expires = false;
	}
}

void Mesh::vertexConfig(const GLvoid *v, GLsizei s)
{
	if (vertices_changed || configured)
		throw runtime_error("Attempt to configure Mesh that is already configured");
	vertices = malloc(s);
	memcpy(vertices, v, s);
	vertices_size = s;
	vertices_changed = true;
}

void Mesh::render(double dtime, ShaderProgram *shader_program)
{
	if (vertices_changed) {
		runVertexConfig();
	}
		
	if (! configured)
		return;

	shader_program->use(); CHECKERR
	
	mat4 model_matrix = effect.getModelMatrix(dtime, pos, size, rotation_axis, rotation_angle); CHECKERR
	
	shader_program->set("model", model_matrix); CHECKERR
	
	glBindVertexArray(VAO); CHECKERR
	for (int i = 0; i < textures.size(); i++) {
		textures[i].bind(); CHECKERR
		glDrawArrays(GL_TRIANGLES, i * vertices_per_texture, vertices_per_texture); CHECKERR
	}
	glBindVertexArray(0); CHECKERR
	glBindTexture(GL_TEXTURE_2D, 0); CHECKERR
}

void Mesh::reset()
{
	removeFromScene();
	pos = vec3(0.0);
	size = vec3(1.0);
	rotation_axis = vec3(0.0, 1.0, 0.0);
	vertices_per_texture = 0;
	textures = {};
	rotation_angle = 0;
	if (VAO) {
		glDeleteVertexArrays(1, &VAO); CHECKERR
	}
	if (VBO) {
		glDeleteBuffers(1, &VAO); CHECKERR
	}
	vertices_changed = false;
	if (vertices) {
		free(vertices);
	}
	vertices = NULL;
	configured = false;
}

void Mesh::addToScene()
{
	scene->add(this);
}

void Mesh::removeFromScene()
{
	scene->remove(this);
}

Mesh::Mesh(Scene *s): scene(s)
{
	reset();
}

void Mesh::runVertexConfig()
{		
	if (! vertices || vertices_size == 0)
		throw runtime_error("Invalid Mesh configuration");
	
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
	vertices_changed = false;
	configured = true;
}
