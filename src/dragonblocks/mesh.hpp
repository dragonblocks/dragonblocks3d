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
			
			glm::mat4 getModelMatrix(double, glm::vec3, glm::vec3, glm::vec3, float, void *);
			
			Effect() = default;
			Effect(Type, void (*)(void *) = nullptr);
			Effect(const Effect &) = default;
			
			private:
			Type type = Type::NONE;
			double time_left;
			void (*on_finish)(void *) = nullptr;
			bool expires;
		};
		
		int vertices_per_texture;
		glm::vec3 pos, size, rotation_axis;
		float rotation_angle = 0;
		std::vector<Texture> textures;
		void *extra_data = nullptr;		
		Effect effect;
		
		void configureVertexObjects(const GLvoid *, GLsizeiptr);
		void render(double dtime, ShaderProgram *);
		void addToScene();
		void removeFromScene();
	
		Mesh(Scene *);

		private:
		GLuint VAO, VBO;
		Scene *scene;
	};
}
