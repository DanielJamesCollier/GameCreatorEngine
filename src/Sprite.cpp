#include "Sprite.h"

#include "TextureCache.h"
#include "GLTexture.h"
#include "RenderingEngine.h"
#include "Shader.h"
#include "Logger.h"
#include "Mesh.h"
#include "cout.h"

#include <glew.h>
#include <vector>

Sprite::Sprite()
	: width(0),
	  height(0)
{
	this->texture = TextureCache::getTexture("Textures/default.png");
	buildSprite();
}

Sprite::Sprite(std::string texture_path)
	: width(0),
	  height(0)
{
	this->texture = TextureCache::getTexture(texture_path);
	buildSprite();
}

Sprite::Sprite(std::string texture_path, unsigned int width, unsigned int height)
	: width(width),
	  height(height)
{
	this->texture = TextureCache::getTexture(texture_path);
	buildSprite();
}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &vao);

	glDeleteBuffers(1, &vertices_buffer);
	glDeleteBuffers(1, &indices_buffer);
}

void Sprite::buildSprite()
{
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(glm::vec3(-0.5, -0.5 - height, 0),  glm::vec2(0, 0))); // bottom left
	vertices.push_back(Vertex(glm::vec3(-0.5, 0.5, 0),   glm::vec2(0, 1 + height))); //top left
	vertices.push_back(Vertex(glm::vec3(0.5 + width, 0.5, 0),  glm::vec2(1.0 + width, 1.0 + height)));  //top right
	vertices.push_back(Vertex(glm::vec3(0.5 + width, -0.5 - height, 0), glm::vec2(1.0 + width, 0)));  //bottom right
	

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	

	/*indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);*/

	this->setName("mesh");
	this->getVerticesCount() = vertices.size();
	this->getIndicesCount() = indices.size();
	this->getFacesCount() = indices.size() / 3;


	// generate all the buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vertices_buffer);
	glGenBuffers(1, &indices_buffer);

	//used to eliminate clutter - instead of calling renderer->getBoundProgram()->hasAttributePosition()
	ShaderProgram* program = ShaderProgramCache::getProgram("sprite shader");

	//add the data to the indices buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//add the data to vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertices_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	// tell opengl how the vertices buffer is layed out
	// tell opengl how the vertices buffer is layed out
	{
		// Positions
		if (program->getAttributeLocation("position") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("position"));
			glVertexAttribPointer(program->getAttributeLocation("position"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		}

		// Texture Coordinates
		if (program->getAttributeLocation("uv") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("uv"));
			glVertexAttribPointer(program->getAttributeLocation("uv"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		}

		// Normals
		if (program->getAttributeLocation("normal") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("normal"));
			glVertexAttribPointer(program->getAttributeLocation("normal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		}

		// Tangents
		if (program->getAttributeLocation("tangent") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("tangent"));
			glVertexAttribPointer(program->getAttributeLocation("tangent"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		}

		// Colours
		if (program->getAttributeLocation("colour") != -1)
		{
			glEnableVertexAttribArray(program->getAttributeLocation("colour"));
			glVertexAttribPointer(program->getAttributeLocation("colour"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
		}
	}

	// unbind the bound arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLTexture* Sprite::getTexture()
{
	return this->texture;
}

unsigned int Sprite::getWidth()
{
	return this->width;
}

unsigned int Sprite::getHeight()
{
	return this->height;
}

void Sprite::render()
{
	renderer->render(this,ShaderProgramCache::getProgram("sprite shader"));
}

void Sprite::update()
{

}