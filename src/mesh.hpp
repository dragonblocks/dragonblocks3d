#pragma once

#include <vector>
#include "gl.hpp"
#include "texture.hpp"

class Frustum;

namespace dragonblocks
{
	class Scene;
	class ShaderProgram;
	
	class Mesh
	{
		public:
		class IAnimation
		{
			public:			
			bool expired(double);
			virtual glm::vec3 getPos(glm::vec3);
			virtual glm::vec3 getSize(glm::vec3);
			virtual glm::vec3 getRotationAxis(glm::vec3);
			virtual float getRotationAngle(float);
			
			protected:
			bool expires = false;
			double time_left;
			void (*on_finish)(void *);
			void *extra_data;
			
			IAnimation() = default;
			IAnimation(double, void (*)(void *), void *);
		};
		
		int vertices_per_texture;
		glm::vec3 pos, size, rotation_axis;
		glm::vec3 minp, maxp;
		float rotation_angle = 0;
		std::vector<Texture> textures;	
		IAnimation *animation = nullptr;		
		bool visible = true;
		
		void render(double dtime, Frustum *, glm::mat4, glm::mat4, glm::vec3);
		bool isRendering();
		void die();
		
		Mesh(Scene *, ShaderProgram *, const GLfloat *, GLsizei);

		private:
		GLuint VAO = 0, VBO = 0;
		Scene *scene;
		ShaderProgram *shader_program;
		GLvoid *vertices = NULL;
		GLsizeiptr vertices_size;
		bool configured = false;
		bool rendering = false;
		bool prepare_death = false;
		bool do_delete = false;
		
		void configure();
		
		~Mesh();
	};
}
