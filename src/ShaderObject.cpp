#include "ShaderObject.h"
#include "Utils.h"
#include "glew.h"
#include <vector>

ShaderObject::ShaderObject(std::string path)
{
	this->file_path = path;
	this->source = loadFileText(path);

	// get file name with the file extensions and set it to the object name
	std::vector<std::string> temp_name_elements = split(path, '/');
	std::string temp_name = temp_name_elements[temp_name_elements.size() - 1];

	// get the file extension
	temp_name_elements = split(temp_name, '.');
	std::string extension = temp_name_elements[temp_name_elements.size() - 1];

	// remove the extension from the name
	for (unsigned int i = 0; i < extension.size(); ++i)	temp_name.pop_back();

	// set the temp name to the name and set the shader type
	this->name = temp_name;

	if (extension == "vs")
	{
		this->object_type = GL_VERTEX_SHADER;
	}
	else
		if (extension == "fs")
		{
		this->object_type = GL_FRAGMENT_SHADER;
		}
		else
			if (extension == "gs")
			{
		this->object_type = GL_GEOMETRY_SHADER;
			}
			else
			{
				printf("shit son the shader type wasnt reconised");
			}

}

ShaderObject::~ShaderObject()
{
}

const std::string& ShaderObject::getSource() const
{
	return this->source;
}

const std::string& ShaderObject::getName() const
{
	return this->name;
}

void ShaderObject::setSource(std::string source)
{
	this->source = source;
}

GLuint& ShaderObject::getID()
{
	return object_id;
}

GLuint& ShaderObject::getType()
{
	return object_type;
}
