#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "gldebug.hpp"
#include "mesh.hpp"
#include "scene.hpp"
#include "shader_program.hpp"

using namespace std;
using namespace glm;
using namespace dragonblocks;

double Mesh::Effect::grow_time = 0.5;	// s
double Mesh::Effect::flyin_time = 0.5;	// s
double Mesh::Effect::flyin_offset = 20;	// m
double Mesh::Effect::rotate_speed = 1;	// turns/s

mat4 Mesh::Effect::getModelMatrix(double dtime, vec3 pos, vec3 size, vec3 rotation_axis, float rotation_angle, void *extra_data)
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

Mesh::Effect::Effect(Mesh::Effect::Type t, void (*callback)(void *))
{
	type = t;
	on_finish = callback;
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

void Mesh::configureVertexObjects(const GLvoid *vertices, GLsizeiptr vertices_size)
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
}

void Mesh::render(double dtime, ShaderProgram *shader_program)
{
	shader_program->use(); CHECKERR
	
	mat4 model_matrix = effect.getModelMatrix(dtime, pos, size, rotation_axis, rotation_angle, extra_data); CHECKERR
	
	shader_program->set("model", model_matrix); CHECKERR
	
	glBindVertexArray(VAO); CHECKERR
	for (int i = 0; i < textures.size(); i++) {
		textures[i].bind(); CHECKERR
		glDrawArrays(GL_TRIANGLES, i * vertices_per_texture, vertices_per_texture); CHECKERR
	}
	glBindVertexArray(0); CHECKERR
	glBindTexture(GL_TEXTURE_2D, 0); CHECKERR
}

void Mesh::addToScene()
{
	scene->add(this);
}

void Mesh::removeFromScene()
{
	scene->remove(this);
}

Mesh::Mesh(Scene *s): pos(0.0), size(1.0), rotation_axis(0.0, 1.0, 0.0), scene(s)
{
}
