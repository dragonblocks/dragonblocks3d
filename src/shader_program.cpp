#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "shader_program.hpp" 

using namespace std;
using namespace glm;
using namespace dragonblocks;

map<string, GLenum> ShaderProgram::shadertypes = {
	{"vertex", GL_VERTEX_SHADER},
	{"fragment", GL_FRAGMENT_SHADER},
};

ShaderProgram::ShaderProgram(const string &global_path)
{
	int success;
	char buffer[1024] = {};
	vector<GLuint> shaders;
	
	id = glCreateProgram();
	
	for (auto it = ShaderProgram::shadertypes.begin(); it != ShaderProgram::shadertypes.end(); it++) {
		const char *c_code;
		GLuint shader;
		string path, code;
		ifstream file;
		stringstream stream;
		
		path = global_path + "/" + it->first + ".glsl";
		file.exceptions(ifstream::failbit | ifstream::badbit);
		file.open(path);
		stream << file.rdbuf();
		code = stream.str();
		c_code = code.c_str();
		
		shader = glCreateShader(it->second);
		shaders.push_back(shader);
		glShaderSource(shader, 1, &c_code, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (! success) {
			glGetShaderInfoLog(shader, 1024, NULL, buffer);
			throw runtime_error("Failed to compile " + it->first + " shader: " + buffer);
		}
		glAttachShader(id, shader);
	}
	
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (! success) {
		glGetProgramInfoLog(id, 1024, NULL, buffer);
		throw runtime_error(string("Failed to link shader program: ") + buffer);
	}
	
	for (auto it = shaders.begin(); it != shaders.end(); it++) {
		glDeleteShader(*it);
	}
}

void ShaderProgram::use() const
{
	glUseProgram(id);
}

void ShaderProgram::set(const string &name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}

void ShaderProgram::set(const string &name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::set(const string &name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::set(const string &name, mat4 value)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
}

void ShaderProgram::set(const string &name, vec3 value)
{
	use();
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}
