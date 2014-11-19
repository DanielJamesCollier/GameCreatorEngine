#pragma once
#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include "GLTexture.h"

#include <unordered_map>
#include <string>

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	static GLTexture* getTexture(std::string path);

private:

	static std::unordered_map<std::string, GLTexture*> texture_cache;

};
#endif

