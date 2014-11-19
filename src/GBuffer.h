#ifndef GBUFFER_H
#define GBUFFER_H
#pragma once

#include <glew.h>

class GBuffer
{
public:

	 GBuffer();
	~GBuffer();

	enum GBUFFER_TEXTURE_TYPE
	{
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

	bool init(unsigned int width, unsigned int height);

	void bindForWriting();
	void bindForReading();

private:

	GLuint fbo;
	GLuint textures[GBUFFER_NUM_TEXTURES];
	GLuint depthTexture;


};

#endif