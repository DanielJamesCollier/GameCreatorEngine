#pragma once
#ifndef SHADERPROGRAMCACHE_H
#define SHADERPROGRAMCACHE_H

#include <string>
#include <unordered_map>

class ShaderProgram;

class ShaderProgramCache
{
public:
	ShaderProgramCache();
	~ShaderProgramCache();

	static void			  addProgram(ShaderProgram* program);
	static ShaderProgram* getProgram(std::string program_name);

	static void clearCache();
	static void deleteProgram(std::string program_name);

private:
	
	static std::unordered_map<std::string /* program name */, ShaderProgram*> cache;

	static ShaderProgram* findProgram(std::string program_name);

};
#endif

