#pragma once
#ifndef SHADEROBJECTCACHE_H
#define SHADEROBJECTCACHE_H

#include <string>
#include <unordered_map>

class ShaderObject; 

class ShaderObjectCache
{
public:
	ShaderObjectCache();
	~ShaderObjectCache();

	static void clearCache();
	static void deleteObject(std::string file_path);

	/*getters and setters*/
	static void addObject(ShaderObject* object);
	static ShaderObject* getObject(std::string file_path);

private:
	
	static std::unordered_map<std::string /*shader file path*/, ShaderObject* /*object*/> cache;

};
#endif

