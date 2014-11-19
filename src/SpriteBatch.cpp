#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	
}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::begin()
{

}

void SpriteBatch::draw(const GLuint& textureId, const glm::vec3& position, const glm::vec2& dimensions, const glm::vec2& uvPosition, const glm::vec2& uvDimension, const glm::vec4& Colour /*= glm::vec4(0,0,0,1)*/)
{
	SpriteInstance* instance = new SpriteInstance();

	instance->textureID = textureId;
	instance->bottomLeft.setPosition(position);

}

void SpriteBatch::draw(const GLuint& textureId,const glm::vec4& spriteBox, const glm::vec4& uvBox, const glm::vec4& Colour /*= glm::vec4(0,0,0,1)*/)
{
	SpriteInstance* instance = new SpriteInstance();

}

void SpriteBatch::draw(const SpriteInstance& instance)  // working progress
{

}

void SpriteBatch::draw() // draws a default sprite - textureCache default sprite
{
	SpriteInstance* instance = new SpriteInstance();

}

void SpriteBatch::end()
{

}

void SpriteBatch::generateBufferData()
{
	glGenVertexArrays(1,&vao);
	glGenBuffers(1,&vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
}