#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <vector>
#include <string>
#include <glm.hpp>
#include <glew.h>
#include <unordered_map>

class ShaderObject;

class ShaderProgram
{
public:

	ShaderProgram(std::string name);
	~ShaderProgram();

	void addShaderObject(ShaderObject *object);
	void link();
	void unbind();
	void bind();

	/* GETTERS AND SETTERS */
	const std::string& getName() const;
	void setUniform1f(std::string uniform, float x);
	void setUniform2f(std::string uniform, float x, float y);
	void setUniform3f(std::string uniform, float x, float y, float z);
	void setUniform4f(std::string uniform, float x, float y, float z, float w);
	void setUniform4m(const std::string& name, const float m[16]);
	void setUniform4m(const std::string& name, glm::mat4& m);

	GLuint getUniformLocation(std::string uniform_name);
	GLuint getAttributeLocation(std::string attribute_name);
	GLuint getID();

	/* method used if you want to explicetly say what location you want to give to the atribute
	THIS METHOD MUST BE USED BEFORE LINKING, otherwise the attributes will assined locations
	by the glsl compiler, to get this locations use the getAttributeLocation() function provided in
	this class
	*/
	void addAttribute(GLuint attribute_location, std::string attribute_name);
	bool isLinked();


private:
	bool linked;

	std::string name;
	GLuint program_id;

	std::vector<ShaderObject*> shader_objects;
	std::unordered_map<std::string /*uniform_name*/, GLuint /*location*/ > uniform_cache;
	std::unordered_map<std::string /*attribute name*/, GLuint /*location*/> attribute_cache;
};
#endif