#include "Shader.h"
#include "Logger.h"
#include "Utils.h"

std::unordered_map<std::string /*shader file path*/, ShaderObject* /*object*/> ShaderObjectCache::cache;

ShaderObjectCache::ShaderObjectCache()
{
}


ShaderObjectCache::~ShaderObjectCache()
{
}

void ShaderObjectCache::clearCache()
{
	for (auto o = cache.begin(); o != cache.end(); ++o)
	{
		delete o->second;
	}
	cache.clear();
}

void ShaderObjectCache::deleteObject(std::string object)
{
	ShaderObject* shader_object = getObject(object);

	if (shader_object != nullptr)
	{
		delete shader_object;
		cache.erase(cache.find(object));
	}
	
	Logger::errorBlock("Object not found", "Error: the object \"" + object + "\" was not found\n and could not be deleted", true);
}

ShaderObject* ShaderObjectCache::getObject(std::string file_path)
{
	auto search = cache.find(file_path);

	if (search != cache.end())
	{
		return search->second;
	} 
	else if (doesFileExist(file_path))
	{
		ShaderObject* object = new ShaderObject(file_path);
		cache.insert(std::make_pair(file_path, object));
		return object;
	}

	Logger::errorBlock("Shader cannot be found", "Shader Path: " + file_path, true);
	return nullptr;
}
