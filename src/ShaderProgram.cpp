#include "ShaderProgram.h"
#include "ShaderObject.h"
#include "Logger.h"
#include "cout.h"

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage);


ShaderProgram::ShaderProgram(std::string name)
	:
	linked(false),
	program_id(0),
	name(name)
{
	this->program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (auto o : shader_objects)
	{
		if (!linked) glDetachShader(program_id, o->getID());
		delete o;
	}

	shader_objects.clear();
	glDeleteProgram(program_id);
}

void ShaderProgram::addShaderObject(ShaderObject *object)
{
	if (object == nullptr) cout << "object is null" << endl;
	if (linked || object == nullptr) return;

	object->getID() = glCreateShader(object->getType());

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = object->getSource().c_str();
	shaderSourceStringLengths[0] = object->getSource().length();

	glShaderSource(object->getID(), 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(object->getID());

	CheckShaderError(object->getID(), GL_COMPILE_STATUS, false, "Shader: " + object->getName() + " - Error:	Failed to Compile");

	glAttachShader(program_id, object->getID());

	shader_objects.push_back(object);
}

const std::string& ShaderProgram::getName() const
{
	return this->name;
}

GLuint ShaderProgram::getUniformLocation(std::string uniform_name)
{
	auto search = uniform_cache.find(uniform_name);

	if (search == uniform_cache.end())
	{
		GLint location = glGetUniformLocation(program_id, uniform_name.c_str());

		if (location != -1)
		{
			cout << "uniform \"" << uniform_name << "\" was found in the shader: location - " << location << endl;
			uniform_cache.insert(std::make_pair(uniform_name, location));
			return location;
		}

		Logger::errorBlock("GLSL Uniform not found", "Uniform Name: " + uniform_name + "\nLocation: " + std::to_string(location) + "Error: uniform not found in the shader or uniform cache", true);
		return location; // returns -1
	}

	// if found in the map return location
	return search->second;
}

GLuint ShaderProgram::getAttributeLocation(std::string attribute_name)
{
	auto search = attribute_cache.find(attribute_name);

	if (search == attribute_cache.end())
	{
		GLint location = glGetAttribLocation(program_id, attribute_name.c_str());

		if (location != -1)
		{
			cout << "attribute \"" << attribute_name << "\"was found in the shader - location: " << location << endl;
			attribute_cache.insert(std::make_pair(attribute_name, location));
			return location;
		}

		Logger::errorBlock("GLSL Attribute not found", "Attribute Name: " + attribute_name + "\nLocation: " + std::to_string(location) + "Error: attribute not found in the shader or attribute cache", false);
		return location; // returns -1
	}

	// if found in the map return location
	return search->second;
}

void ShaderProgram::link()
{
	if (linked || shader_objects.empty()) return;
	linked = true;

	glLinkProgram(program_id);
	CheckShaderError(program_id, GL_LINK_STATUS, true, "Program: " + this->getName() + " failed to link");

	for (auto a : shader_objects)
	{
		glDetachShader(program_id, a->getID());
	}
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::bind()
{
	glUseProgram(program_id);
}

void ShaderProgram::setUniform1f(std::string uniform, float x)
{
	glUniform1f(getUniformLocation(uniform), x);
}

void ShaderProgram::setUniform2f(std::string uniform, float x, float y)
{
	glUniform2f(getUniformLocation(uniform), x, y);
}

void ShaderProgram::setUniform3f(std::string uniform, float x, float y, float z)
{
	glUniform3f(getUniformLocation(uniform), x, y, z);
}

void ShaderProgram::setUniform4f(std::string uniform, float x, float y, float z, float w)
{
	glUniform4f(getUniformLocation(uniform), x, y, z, w);
}


void ShaderProgram::setUniform4m(const std::string& name, const float m[16])
{
	glProgramUniformMatrix4fv(getID(),getUniformLocation(name), 1, false, m);
}

void ShaderProgram::setUniform4m(const std::string& name, glm::mat4& m)
{
	glProgramUniformMatrix4fv(getID(), getUniformLocation(name), 1, false, &m[0][0]);
}

bool ShaderProgram::isLinked()
{
	return this->linked;
}

GLuint ShaderProgram::getID()
{
	return program_id;
}

static void CheckShaderError(int shader, int flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (!success)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		Logger::errorBlock(errorMessage, error, true);
	}
}