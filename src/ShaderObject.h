#pragma once
#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include <string>
#include <glew.h>

class ShaderObject
{
public:
	ShaderObject(std::string path);
	~ShaderObject();

	/* GETTERS AND SETTERS */
	const std::string& getSource() const;
	const std::string& getName() const;
	void setSource(std::string source);
	GLuint& getID();
	GLuint& getType();

private:
	std::string name;
	std::string file_path;
	std::string source;

	GLuint object_id;
	GLuint object_type;
};

#endif
