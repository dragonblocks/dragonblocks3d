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

double Mesh::Animation::grow_time = 0.25;	// s
double Mesh::Animation::flyin_time = 0.4;	// s
double Mesh::Animation::flyin_offset = 20;	// m
double Mesh::Animation::rotate_speed = 1;	// turns/s

mat4 Mesh::Animation::getModelMatrix(double dtime, vec3 pos, vec3 size, vec3 rotation_axis, float rotation_angle)
{
	mat4 trans = mat4(1.0);

	if (type == Mesh::Animation::Type::NONE)
		goto finish;

	if (expires) {
		time_left -= dtime;
		if (time_left < 0) {
			type = Mesh::Animation::Type::NONE;
			if (on_finish) {
				(*on_finish)(extra_data);
			}
			goto finish;
		}
	}	

	switch (type) {
		case Mesh::Animation::Type::FLYIN:
		pos.y -= Mesh::Animation::flyin_offset * time_left / Mesh::Animation::flyin_time;
		break;
		
		case Mesh::Animation::Type::GROW:
		size *= 1 - time_left / Mesh::Animation::grow_time;
		break;
		
		case Mesh::Animation::Type::ROTATE:
		rotation_angle += glfwGetTime() * Mesh::Animation::rotate_speed * pi<float>() * 2;
	}

	finish:
	
	trans = translate(trans, pos);
	trans = rotate(trans, rotation_angle, rotation_axis);
	trans = scale(trans, size);
	
	return trans;
}

Mesh::Animation::Animation(Mesh::Animation::Type t, void (*o)(void *), void *e) : type(t), on_finish(o), extra_data(e)
{
	switch(type) {
		case Mesh::Animation::Type::FLYIN:
		expires = true;
		time_left = Mesh::Animation::flyin_time;
		break;
		
		case Mesh::Animation::Type::GROW:
		expires = true;
		time_left = Mesh::Animation::grow_time;
		break;
		
		case Mesh::Animation::Type::ROTATE:
		expires = false;
		break;
	}
}

void Mesh::render(double dtime, ShaderProgram *shader_program)
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
	
	mat4 model_matrix = animation.getModelMatrix(dtime, pos, size, rotation_axis, rotation_angle); CHECKERR
	
	shader_program->set("model", model_matrix); CHECKERR
	
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

Mesh::Mesh(Scene *s, const GLvoid *v, GLsizei vs): pos(0), size(1), rotation_axis(0, 1, 0), scene(s), vertices_size(vs)
{
	if (! v || ! vs)
		throw runtime_error("Invalid Mesh configuration");
	vertices = malloc(vs);
	memcpy(vertices, v, vs);
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
