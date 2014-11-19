#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"
#include <glew.h>

class ShaderProgram;
class GLTexture;

class Sprite : public GameObject
{
public:
	Sprite();
	Sprite(std::string texture_path);
	Sprite(std::string texture_path, unsigned int width, unsigned int height);
	~Sprite();

	unsigned int* getVAO_Id(void)							 { return &vao; }
	unsigned int  getIndicesBufferId(void) const			 { return indices_buffer; }

	GLTexture* getTexture();
	unsigned int getWidth();
	unsigned int getHeight();

	// gameobject overloaded functions
	void update();
	void render();

private: 

	GLuint vao;
	GLuint vertices_buffer;
	GLuint indices_buffer;

	ShaderProgram* shader_program;
	GLTexture* texture;

	unsigned int width;
	unsigned int height;

	void buildSprite();

};
#endif

