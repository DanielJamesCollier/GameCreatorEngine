#include "Shader.h"
#include "Logger.h"
#include "cout.h"

std::unordered_map<std::string /* program name */, ShaderProgram*> ShaderProgramCache::cache;

ShaderProgramCache::ShaderProgramCache()
{
	ShaderProgram* default_program = new ShaderProgram("default shader");
	default_program->addShaderObject(ShaderObjectCache::getObject("Shaders/Basic.vs"));
	default_program->addShaderObject(ShaderObjectCache::getObject("Shaders/Basic.fs"));
	default_program->link();


	ShaderProgram* sprite_program = new ShaderProgram("sprite shader");
	sprite_program->addShaderObject(ShaderObjectCache::getObject("Shaders/Sprite.vs"));
	sprite_program->addShaderObject(ShaderObjectCache::getObject("Shaders/Sprite.fs"));
	sprite_program->link();

	// add both programs to the cache
	this->addProgram(default_program);
	this->addProgram(sprite_program);
}


ShaderProgramCache::~ShaderProgramCache()
{
	ShaderObjectCache::clearCache();
	clearCache();
}

void ShaderProgramCache::addProgram(ShaderProgram* program)
{
	cache.insert(std::make_pair(program->getName(),program));
}

ShaderProgram* ShaderProgramCache::getProgram(std::string program_name)
{
	return findProgram(program_name);
}

void ShaderProgramCache::clearCache()
{
	for (auto i = cache.begin(); i != cache.end(); ++i)
	{
		delete  i->second;
	}
	cache.clear();
}

void ShaderProgramCache::deleteProgram(std::string program_name)
{
	ShaderProgram* program = findProgram(program_name);

	if (program != nullptr)
	{
		delete program;
		cache.erase(program_name);
	}
	else
	{
		Logger::errorBlock("Shader Program Could Not Be Deleted", "Error: the program could not be found in the shader program cache", true);
	}
}

ShaderProgram* ShaderProgramCache::findProgram(std::string program_name)
{
	auto search = cache.find(program_name);

	if (search != cache.end())
	{
		return search->second;
	}

	Logger::errorBlock("Shader Program Could Not Be Found", "Error: the program could not be found in the shader program cache", true);
	
	return nullptr;
}
