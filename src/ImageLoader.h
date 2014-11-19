#pragma once
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "GLTexture.h"

#include <string>

class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	static GLTexture* loadTexture(std::string file_path, unsigned int texture_type,bool &found);
	static GLTexture* loadPNGTexture(std::string file_path, bool &found);

private:

};

#endif