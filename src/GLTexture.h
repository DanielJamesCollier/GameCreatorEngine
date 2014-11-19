#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glew.h>

struct GLTexture
{
	GLuint texture_id;
	GLuint texture_type;
	GLuint width;
	GLuint height;
};
#endif

