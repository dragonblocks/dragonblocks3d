#pragma once

#include <map>
#include <string>
#include "gl.hpp"

namespace dragonblocks
{
	class ShaderProgram
	{
		public:
		static std::map<std::string, GLenum> shadertypes;
		
		void use() const;
		void set(const std::string &, bool);
		void set(const std::string &, int);
		void set(const std::string &, float);
		void set(const std::string &, glm::mat4);
		void set(const std::string &, glm::vec3);
		
		ShaderProgram(const std::string &);
		~ShaderProgram();
		
		private:
		GLuint id;
	};
}
