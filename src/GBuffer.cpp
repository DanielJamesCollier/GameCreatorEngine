#include "GBuffer.h"

GBuffer::GBuffer()
{

}

GBuffer::~GBuffer()
{

}

bool GBuffer::init(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenTextures(GBUFFER_NUM_TEXTURES, textures);
	glGenTextures(1, &depthTexture);

	for (unsigned int i = 0; i < GBUFFER_NUM_TEXTURES; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	}

	return false;
}