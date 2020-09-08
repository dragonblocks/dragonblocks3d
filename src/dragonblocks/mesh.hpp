#pragma once

#include <vector>
#include "gl.hpp"
#include "texture.hpp"

namespace dragonblocks
{
	class Scene;
	class ShaderProgram;
	
	class Mesh
	{
		public:
		class Effect
		{
			public:
			static double grow_time;	// s
			static double flyin_time;	// s
			static double flyin_offset;	// m
			static double rotate_speed;	// turns/s
			
			enum Type
			{
				NONE,
				FLYIN,
				GROW,
				ROTATE
			};
			
			glm::mat4 getModelMatrix(double, glm::vec3, glm::vec3, glm::vec3, float);
			
			Effect() = default;
			Effect(Type, void (*)(void *) = nullptr, void * = nullptr);
			Effect(const Effect &) = default;
			
			private:
			Type type = Type::NONE;
			double time_left;
			void (*on_finish)(void *);
			void *extra_data;
			bool expires;
		};
		
		int vertices_per_texture;
		glm::vec3 pos, size, rotation_axis;
		float rotation_angle;
		std::vector<Texture> textures;	
		Effect effect;
		
		void reset();
		void vertexConfig(const GLvoid *v, GLsizei s);
		void render(double dtime, ShaderProgram *);
		void addToScene();
		void removeFromScene();
		void runVertexConfig();
		
		Mesh(Scene *);

		private:
		GLuint VAO = 0, VBO = 0;
		Scene *scene;
		GLvoid *vertices = NULL;
		GLsizeiptr vertices_size;
		bool configured;
		bool vertices_changed;
		
	};
}
