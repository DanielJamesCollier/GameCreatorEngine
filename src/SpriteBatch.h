#pragma once
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "glew.h"
#include "Vertex.h"
#include "glm.hpp"
#include "Sprite.h"

#include <vector>

struct SpriteInstance
{
public:
	GLuint textureID;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class SpriteBatch
{
public:
	 SpriteBatch();
	~SpriteBatch();

	void begin();
	void end(); // sorts the batch into batch groups and then renders to the screen

	void draw(const GLuint& textureId, const glm::vec3& position, const glm::vec2& dimensions, const glm::vec2& uvPosition, const glm::vec2& uvDimension, const glm::vec4& Colour = glm::vec4(0,0,0,1));
	void draw(const GLuint& textureId,const glm::vec4& spriteBox, const glm::vec4& uvBox, const glm::vec4& Colour = glm::vec4(0,0,0,1));
	void draw(const SpriteInstance& instance);  // working progress
	void draw(); // draws a default sprite - textureCache default sprite

private:

	GLuint vao;
	GLuint vbo;
	
	vector<SpriteInstance*> spriteInstances; 

	void generateBufferData();
};

#endif