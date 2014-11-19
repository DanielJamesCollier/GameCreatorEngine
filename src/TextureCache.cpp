#include "TextureCache.h"
#include "ImageLoader.h"
#include "Logger.h"
#include "cout.h"

#include <glew.h>

std::unordered_map<std::string, GLTexture*> TextureCache::texture_cache;

TextureCache::TextureCache()
{
	getTexture("Textures/default.png");

	Logger::infoBlock("Texture Cache info", "Cached Textures: " + std::to_string(texture_cache.size()), true);
}


TextureCache::~TextureCache()
{
	for (auto i = texture_cache.begin(); i != texture_cache.end(); ++i)
	{
		glDeleteTextures(1,&i->second->texture_id);
		delete i->second;
	}

	texture_cache.clear();
}

GLTexture* TextureCache::getTexture(std::string path)
{
	auto pair_lookup = texture_cache.find(path);

	if (pair_lookup == texture_cache.end())
	{
		// texture not found in chache - so add it

		Logger::errorBlock("texture not found in cache", "path: " + path + "\nsolution: loading texure and adding to cache", true);

		bool textureLoaded;
		GLTexture* texture = ImageLoader::loadTexture(path, GL_TEXTURE_2D, textureLoaded);

		if (textureLoaded) texture_cache.insert(std::make_pair(path, texture));

		return texture;
	}
	else
	{
		// chache texture found
		
		return pair_lookup->second;
	}
}
