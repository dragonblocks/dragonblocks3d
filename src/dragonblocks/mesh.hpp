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
		class Animation
		{
			public:
			static double grow_time;
			static double flyin_time;
			static double flyin_offset;
			static double rotate_speed;
			
			enum Type
			{
				NONE,
				FLYIN,
				GROW,
				ROTATE
			};
			
			glm::mat4 getModelMatrix(double, glm::vec3, glm::vec3, glm::vec3, float);
			
			Animation() = default;
			Animation(Type, void (*)(void *) = nullptr, void * = nullptr);
			Animation(const Animation &) = default;
			
			private:
			Type type = Type::NONE;
			double time_left;
			void (*on_finish)(void *);
			void *extra_data;
			bool expires;
		};
		
		int vertices_per_texture;
		glm::vec3 pos, size, rotation_axis;
		float rotation_angle = 0;
		std::vector<Texture> textures;	
		Animation animation;		
		
		void render(double dtime, ShaderProgram *);
		bool isRendering();
		void die();
		
		Mesh(Scene *, const GLvoid *, GLsizei);
		~Mesh();

		private:
		GLuint VAO = 0, VBO = 0;
		Scene *scene;
		GLvoid *vertices = NULL;
		GLsizeiptr vertices_size;
		bool configured = false;
		bool rendering = false;
		bool prepare_death = false;
		bool do_delete = false;
		
		void configure();
	};
}
