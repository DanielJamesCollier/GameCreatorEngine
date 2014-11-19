#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "glm.hpp"
#include "cout.h"

struct Vertex
{
	Vertex()
	{

	}
	Vertex(const glm::vec3& position, const glm::vec2& texCoord = glm::vec2(0, 0), const glm::vec3& normal = glm::vec3(0, 0, 0), const glm::vec3 tangent = glm::vec3(0, 0, 0), const glm::vec4 colour = glm::vec4(0, 0, 0, 1))
	{
		this->pos = position;
		this->texCoord = texCoord;
		this->normal = normal;
		this->tangent = tangent;
		this->colour = colour;
	}

	inline glm::vec3& getPosition() { return pos; }
	inline glm::vec2& getTexCoord() { return texCoord; }
	inline glm::vec3& getNormal()	{ return normal; }
	inline glm::vec3& getTangent()	{ return tangent; }
	inline glm::vec4& getColour()	{ return colour; }

	inline void setPosition(const glm::vec3& pos) { this->pos = pos; }
	inline void setTexCord(const glm::vec2& tex) { this->texCoord = tex; }
	inline void setNormals(const glm::vec3& norm) { this->normal = norm; }
	inline void setTangent(const glm::vec3& tan) { this->tangent = tan; }
	inline void setColour(const glm::vec4& col) { this->colour = col; }

	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec4 colour;
};
#endif